#include "PlayFieldGridComponent.h"
#include <iostream>

pacman::PlayFieldGridComponent::PlayFieldGridComponent(amu::GameObject* ownerObjectPtr, int rowsGrid, int colsGrid)
	: amu::Component(ownerObjectPtr)
	, m_RowsGrid{ rowsGrid }
	, m_ColsGrid{ colsGrid }
	, m_TileVec{ std::vector<TileType>{ static_cast<std::uint64_t>(m_RowsGrid * m_ColsGrid) } }
{
}

void pacman::PlayFieldGridComponent::SetElement(std::int64_t const& rowIdx, std::int64_t const& colIdx, std::string_view const& typeString)
{
	using tile = pacman::PlayFieldGridComponent::TileType;
	std::cout << "[" << rowIdx << ", " << colIdx << "] = " << typeString << "\n";
	if (typeString == "pathway")
	{
		m_TileVec[GetIndex(rowIdx, colIdx)] = tile::Pathway;
		return;
	}
	else if (typeString == "wall")
	{
		m_TileVec[GetIndex(rowIdx, colIdx)] = tile::Wall;
		return;
	}
	else if (typeString == "void")
	{
		m_TileVec[GetIndex(rowIdx, colIdx)] = tile::Void;
		return;
	}
	throw std::runtime_error(std::string("No valid tile type") + std::string(typeString));
}

[[nodiscard]] std::int64_t pacman::PlayFieldGridComponent::GetIndex(std::int64_t const& rowIdx, std::int64_t const& colIdx) const
{
	return colIdx + m_ColsGrid * rowIdx;
}
