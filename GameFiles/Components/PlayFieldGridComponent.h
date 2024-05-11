#ifndef PM_PLAY_FIELD_GRID_H
#define PM_PLAY_FIELD_GRID_H

#include "Configuration.h"
#include "Component.h"
#include <glm/glm.hpp>

namespace pacman
{

	class PlayFieldGridComponent final : public amu::Component
	{
	public:
		enum class TileType
		{
			Void,
			Pathway,
			Wall
		};

		struct Tile
		{
			glm::ivec2 TopLeft{ 0, 0 };
			TileType Type{ TileType::Void };
		};

		PlayFieldGridComponent(amu::GameObject* ownerObjectPtr, std::int64_t const& rowsGrid, std::int64_t const& colsGrid, std::int64_t const& cellSize, std::int64_t const& cellHeigth);
		virtual ~PlayFieldGridComponent() override = default;

		PlayFieldGridComponent(PlayFieldGridComponent const& other) = delete;
		PlayFieldGridComponent(PlayFieldGridComponent&& other) = delete;
		PlayFieldGridComponent& operator=(PlayFieldGridComponent const& other) = delete;
		PlayFieldGridComponent& operator=(PlayFieldGridComponent&& other) = delete;

		void SetTileType(std::int64_t const& rowIdx, std::int64_t const& colIdx, std::string_view const& typeString);

	private:
		std::int64_t const m_RowsGrid{};
		std::int64_t const m_ColsGrid{};
		std::int64_t const m_CellSize{};
		std::vector<Tile> m_TileVec{};

		[[nodiscard]] std::int64_t GetIndex(std::int64_t const& rowIdx, std::int64_t const& colIdx) const;
	};

}

#endif