#include "PlayFieldGridComponent.h"

pacman::PlayFieldGridComponent::PlayFieldGridComponent(amu::GameObject* ownerObjectPtr, std::uint64_t const& rowsGrid, std::uint64_t const& colsGrid, std::uint64_t const& cellWidth, std::uint64_t const& cellHeigth)
	: amu::Component(ownerObjectPtr)
	, m_RowsGrid{ rowsGrid }
	, m_ColsGrid{ colsGrid }
	, m_TileDimensions{ cellWidth, cellHeigth }
	, m_TileVec{ std::vector<Tile>{ static_cast<std::uint64_t>(m_RowsGrid * m_ColsGrid) } }
{
	assert(std::size(m_TileVec) == m_ColsGrid * m_RowsGrid);

	for (int rowIdx{}; rowIdx < m_RowsGrid; ++rowIdx)
	{
		for (int colIdx{}; colIdx < m_ColsGrid; ++colIdx)
		{
			m_TileVec[GetIndex(rowIdx, colIdx)].Center = glm::vec2{ colIdx * cellWidth + cellWidth / 2, rowIdx * cellHeigth + cellHeigth / 2};
		}
	}
}

void pacman::PlayFieldGridComponent::SetTileType(std::uint64_t const& rowIdx, std::uint64_t const& colIdx, std::string_view const& typeString)
{
	std::int64_t const idx{ GetIndex(rowIdx, colIdx) };
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
	throw std::runtime_error(std::string("No valid tile type") + std::string(typeString));
}

glm::vec2 const& pacman::PlayFieldGridComponent::GetTileDimensions() const
{
	return m_TileDimensions;
}

pacman::PlayFieldGridComponent::Tile const& pacman::PlayFieldGridComponent::GetTile(std::uint64_t const& rowIdx, std::uint64_t const& colIdx) const
{
	return m_TileVec[GetIndex(rowIdx, colIdx)];
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
	
[[nodiscard]] std::int64_t pacman::PlayFieldGridComponent::GetIndex(std::uint64_t const& rowIdx, std::uint64_t const& colIdx) const
{
	return rowIdx * m_ColsGrid + colIdx;
}
