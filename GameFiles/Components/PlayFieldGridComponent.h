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
			Crossing,
			Wall,
			Teleport
		};

		struct Tile
		{
			glm::vec2 Center{ 0, 0 };
			TileType Type{ TileType::Void };
		};

		PlayFieldGridComponent(amu::GameObject* ownerObjectPtr, std::uint64_t const& rowsGrid, std::uint64_t const& colsGrid, std::uint64_t const& cellSize, std::uint64_t const& cellHeigth);
		virtual ~PlayFieldGridComponent() override = default;

		PlayFieldGridComponent(PlayFieldGridComponent const&) = delete;
		PlayFieldGridComponent(PlayFieldGridComponent&&) = delete;
		PlayFieldGridComponent& operator=(PlayFieldGridComponent const&) = delete;
		PlayFieldGridComponent& operator=(PlayFieldGridComponent&&) = delete;

		void SetTileType(std::uint64_t const& rowIdx, std::uint64_t const& colIdx, std::string_view const& typeString);

		glm::vec2 const& GetTileDimensions() const;

		Tile const& GetTile(std::uint64_t const& rowIdx, std::uint64_t const& colIdx) const;
		Tile const& GetTile(glm::vec2 const& position) const;

		Tile const& GetTileToTeleportTo(Tile const& currentTile);
	private:
		std::uint64_t const m_RowsGrid{};
		std::uint64_t const m_ColsGrid{};
		glm::vec2 const m_TileDimensions{};

		std::vector<Tile> m_TileVec{};

		std::vector<Tile> m_TeleportTileVec{};

		[[nodiscard]] std::int64_t GetIndex(std::uint64_t const& rowIdx, std::uint64_t const& colIdx) const;
	};

}

#endif