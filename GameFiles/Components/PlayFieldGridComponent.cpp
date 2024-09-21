#include "PlayFieldGridComponent.h"
#include "SceneManager.h"
#include "Subject.h"
#include "RenderComponent.h"
#include "Colliders/BigPickupCollider.h"
#include "Colliders/SmallPickupCollider.h"

pacman::PlayFieldGridComponent::PlayFieldGridComponent(amu::GameObject* ownerObjectPtr, std::uint64_t const& rowsGrid, std::uint64_t const& colsGrid, std::uint64_t const& cellWidth, std::uint64_t const& cellHeigth)
	: amu::Component(ownerObjectPtr)
	, m_RowsGrid{ rowsGrid }
	, m_ColsGrid{ colsGrid }
	, m_TileDimensions{ cellWidth, cellHeigth }
	, m_TileVec{ std::vector<Tile>{ static_cast<unsigned int>(m_RowsGrid * m_ColsGrid) } }
{
	assert(std::size(m_TileVec) == m_ColsGrid * m_RowsGrid);

	for (int rowIdx{}; rowIdx < m_RowsGrid; ++rowIdx)
	{
		for (int colIdx{}; colIdx < m_ColsGrid; ++colIdx)
		{
			m_TileVec[static_cast<int>(GetIndex(rowIdx, colIdx))].Center = glm::vec2{ static_cast<float>(colIdx * cellWidth + cellWidth / 2), static_cast<float>(rowIdx * cellHeigth + cellHeigth / 2)};
		}
	}
}

void pacman::PlayFieldGridComponent::SetTileType(std::uint64_t const& rowIdx, std::uint64_t const& colIdx, std::string_view const& typeString)
{
	int const idx{ static_cast<int>(GetIndex(rowIdx, colIdx)) };
	if (typeString == "pathway")
	{
		m_TileVec[idx].Type = TileType::Pathway;
		return;
	}
	else if (typeString == "wall")
	{
		m_TileVec[idx].Type = TileType::Wall;
		return;
	}
	else if (typeString == "void")
	{
		m_TileVec[idx].Type = TileType::Void;
		return;
	}
	else if (typeString == "crossing")
	{
		m_TileVec[idx].Type = TileType::Crossing;
		return;
	}
	else if (typeString == "teleport")
	{
		m_TileVec[idx].Type = TileType::Teleport;
		m_TeleportTileVec.emplace_back(m_TileVec[idx]);
		return;
	}
}

glm::vec2 const& pacman::PlayFieldGridComponent::GetTileDimensions() const
{
	return m_TileDimensions;
}

pacman::PlayFieldGridComponent::Tile const& pacman::PlayFieldGridComponent::GetTile(std::uint64_t const& rowIdx, std::uint64_t const& colIdx) const
{
	return m_TileVec[static_cast<int>(GetIndex(rowIdx, colIdx))];
}

pacman::PlayFieldGridComponent::Tile const& pacman::PlayFieldGridComponent::GetTile(glm::vec2 const& position) const
{
	auto closestTileFinder =
		[&](Tile const& tile1, Tile const& tile2) -> bool
		{
			return
				(position.x - tile1.Center.x) * (position.x - tile1.Center.x) + (position.y - tile1.Center.y) * (position.y - tile1.Center.y)
				<
				(position.x - tile2.Center.x) * (position.x - tile2.Center.x) + (position.y - tile2.Center.y) * (position.y - tile2.Center.y);
		};

	return *std::min_element(std::execution::par_unseq, m_TileVec.begin(), m_TileVec.end(), closestTileFinder);
}

pacman::PlayFieldGridComponent::Tile const& pacman::PlayFieldGridComponent::GetTileToTeleportTo(Tile const& currentTile)
{
	auto otherTileFinder =
		[&](Tile const& tile)
		{
			if (currentTile.Center == tile.Center and
				currentTile.Center.x == tile.Center.x and
				currentTile.Center.y == tile.Center.y)
			{
				return false;
			}
			return true;
		};
	auto it = std::find_if(m_TeleportTileVec.begin(), m_TeleportTileVec.end(), otherTileFinder);
	return *it;
}

void pacman::PlayFieldGridComponent::SpawnSmallPickup(amu::Scene* scenePtr, glm::vec2 const& location)
{
	std::unique_ptr pickupSmallUPtr{ std::make_unique<amu::GameObject>() };
	pickupSmallUPtr->SetTag(tags::PICKUP_SMALL);

	pickupSmallUPtr->AddComponent<amu::TransformComponent>(pickupSmallUPtr.get(), location);

	amu::RenderComponent* renderComponentPtr{ pickupSmallUPtr->AddComponent<amu::RenderComponent>(pickupSmallUPtr.get(), resources::sprites::PICKUP_SMALL.FilePath) };
	renderComponentPtr->SetSourceRectangle(SDL_Rect{ 0, 0, renderComponentPtr->GetSize().x, renderComponentPtr->GetSize().y });

	pickupSmallUPtr->AddCollider(std::make_unique<SmallPickupCollider>(pickupSmallUPtr.get()));
	SmallPickupCollider* collPtr{ dynamic_cast<SmallPickupCollider*>(pickupSmallUPtr->GetCollider()) };
	collPtr->AddObserver(this);

	scenePtr->Add(std::move(pickupSmallUPtr));
}

void pacman::PlayFieldGridComponent::SpawnBigPickup(amu::Scene* scenePtr, glm::vec2 const& location)
{
	std::unique_ptr pickupBigUPtr{ std::make_unique<amu::GameObject>() };
	pickupBigUPtr->SetTag(tags::PICKUP_BIG);

	pickupBigUPtr->AddComponent<amu::TransformComponent>(pickupBigUPtr.get(), location);

	amu::RenderComponent* renderComponentPtr{ pickupBigUPtr->AddComponent<amu::RenderComponent>(pickupBigUPtr.get(), resources::sprites::PICKUP_BIG.FilePath) };
	renderComponentPtr->SetSourceRectangle(SDL_Rect{ 0, 0, renderComponentPtr->GetSize().x, renderComponentPtr->GetSize().y });

	pickupBigUPtr->AddCollider(std::make_unique<BigPickupCollider>(pickupBigUPtr.get()));
	BigPickupCollider* collPtr{ dynamic_cast<BigPickupCollider*>(pickupBigUPtr->GetCollider()) };
	collPtr->AddObserver(this);

	scenePtr->Add(std::move(pickupBigUPtr));
}

void pacman::PlayFieldGridComponent::AddPickupSpawnLocation(glm::vec2 const& spawnLocation, std::string_view const& type)
{
	m_PickupRespawnSpawnLocationVec.emplace_back(std::make_pair(spawnLocation, type));
}

void pacman::PlayFieldGridComponent::OnNotify(Event eventType, amu::Subject* subjectPtr)
{
	if (eventType == events::SMALL_PICKUP_VANISHED or eventType == events::BIG_PICKUP_VANISHED)
	{
		amu::GameObject* subjectOwnerPtr{ subjectPtr->GetSubjectOwner() };
		AddPickupSpawnLocation(subjectOwnerPtr->GetComponent<amu::TransformComponent>()->GetWorldPosition(), subjectOwnerPtr->GetTag());
	}

	if (eventType == events::PACMAN_DYING_ANIM_FINISHED || eventType == events::PACMAN_ATE_ALL)
	{
		amu::Scene* currScenePtr = amu::SceneManager::GetInstance().GetSceneByName(tags::MAIN_SCENE);
		for (auto& [loc, tag]: m_PickupRespawnSpawnLocationVec)
		{
			if (tag == tags::PICKUP_SMALL)
			{
				SpawnSmallPickup(currScenePtr, loc);
			}
			else if (tag == tags::PICKUP_BIG)
			{
				SpawnBigPickup(currScenePtr, loc);
			}
		}
	}
}
	
[[nodiscard]] std::int64_t pacman::PlayFieldGridComponent::GetIndex(std::uint64_t const& rowIdx, std::uint64_t const& colIdx) const
{
	return rowIdx * m_ColsGrid + colIdx;
}
