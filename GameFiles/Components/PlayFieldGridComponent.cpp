#include "PlayFieldGridComponent.h"

pacman::PlayFieldGridComponent::PlayFieldGridComponent(amu::GameObject* ownerObjectPtr, std::int64_t const& rowsGrid, std::int64_t const& colsGrid, std::int64_t const& cellWidth, std::int64_t const& cellHeigth)
	: amu::Component(ownerObjectPtr)
	, m_RowsGrid{ rowsGrid }
	, m_ColsGrid{ colsGrid }
	, m_CellSize{ cellWidth }
	, m_TileVec{ std::vector<Tile>{ static_cast<std::uint64_t>(m_RowsGrid * m_ColsGrid) } }
{
	assert(std::ssize(m_TileVec) == m_ColsGrid * m_RowsGrid);

	for (int rowIdx{}; rowIdx < m_RowsGrid; ++rowIdx)
	{
		for (int colIdx{}; colIdx < m_ColsGrid; ++colIdx)
		{
			m_TileVec[GetIndex(rowIdx, colIdx)].Center = glm::ivec2{ rowIdx * cellHeigth + cellHeigth / 2, colIdx * cellWidth + cellWidth / 2 };
		}
	}
}

void pacman::PlayFieldGridComponent::SetTileType(std::int64_t const& rowIdx, std::int64_t const& colIdx, std::string_view const& typeString)
{
	std::cout	<< "[" << rowIdx << ", " << colIdx 
				<< "] = " << typeString 
				<< ", center is: " << m_TileVec[GetIndex(rowIdx, colIdx)].Center.x << ", " << m_TileVec[GetIndex(rowIdx, colIdx)].Center.y
				<< "\n";

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

	throw std::runtime_error(std::string("No valid tile type") + std::string(typeString));
}

[[nodiscard]] std::int64_t pacman::PlayFieldGridComponent::GetIndex(std::int64_t const& rowIdx, std::int64_t const& colIdx) const
{
	return colIdx + m_ColsGrid * rowIdx;
}
