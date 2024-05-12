#include "PlayFieldGridComponent.h"

pacman::PlayFieldGridComponent::PlayFieldGridComponent(amu::GameObject* ownerObjectPtr, std::int64_t const& rowsGrid, std::int64_t const& colsGrid, std::int64_t const& cellWidth, std::int64_t const& cellHeigth)
	: amu::Component(ownerObjectPtr)
	, m_RowsGrid{ rowsGrid }
	, m_ColsGrid{ colsGrid }
	, m_TileDimensions{ cellWidth, cellHeigth }
	, m_TileVec{ std::vector<Tile>{ static_cast<std::uint64_t>(m_RowsGrid * m_ColsGrid) } }
{
	assert(std::ssize(m_TileVec) == m_ColsGrid * m_RowsGrid);

	for (int rowIdx{}; rowIdx < m_RowsGrid; ++rowIdx)
	{
		for (int colIdx{}; colIdx < m_ColsGrid; ++colIdx)
		{
			m_TileVec[GetIndex(rowIdx, colIdx)].Center = glm::vec2{ colIdx * cellWidth + cellWidth / 2, rowIdx * cellHeigth + cellHeigth / 2};
		}
	}
}

void pacman::PlayFieldGridComponent::SetTileType(std::int64_t const& rowIdx, std::int64_t const& colIdx, std::string_view const& typeString)
{
	//std::cout	<< "[" << rowIdx << ", " << colIdx 
	//			<< "] = " << typeString 
	//			<< ", top left is: " << m_TileVec[GetIndex(rowIdx, colIdx)].TopLeft.x << ", " << m_TileVec[GetIndex(rowIdx, colIdx)].TopLeft.y
	//			<< "\n";

	if (typeString == "pathway")
	{
		m_TileVec[GetIndex(rowIdx, colIdx)].Type = TileType::Pathway;
		return;
	}
	else if (typeString == "wall")
	{
		m_TileVec[GetIndex(rowIdx, colIdx)].Type = TileType::Wall;
		return;
	}
	else if (typeString == "void")
	{
		m_TileVec[GetIndex(rowIdx, colIdx)].Type = TileType::Void;
		return;
	}
	else if (typeString == "crossing")
	{
		m_TileVec[GetIndex(rowIdx, colIdx)].Type = TileType::Crossing;
		return;
	}
	else if (typeString == "teleport")
	{
		m_TileVec[GetIndex(rowIdx, colIdx)].Type = TileType::Teleport;
		return;
	}
	throw std::runtime_error(std::string("No valid tile type") + std::string(typeString));
}

glm::vec2 const& pacman::PlayFieldGridComponent::GetTileDimensions() const
{
	return m_TileDimensions;
}

pacman::PlayFieldGridComponent::Tile const& pacman::PlayFieldGridComponent::GetTile(std::int64_t const& rowIdx, std::int64_t const& colIdx) const
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
	
[[nodiscard]] std::int64_t pacman::PlayFieldGridComponent::GetIndex(std::int64_t const& rowIdx, std::int64_t const& colIdx) const
{
	return rowIdx * m_ColsGrid + colIdx;
}
