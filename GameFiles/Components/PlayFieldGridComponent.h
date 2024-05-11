#ifndef PM_PLAY_FIELD_GRID_H
#define PM_PLAY_FIELD_GRID_H

#include "Configuration.h"
#include "Component.h"

namespace pacman
{

	class PlayFieldGridComponent : public amu::Component
	{
	public:
		enum class TileType
		{
			Void,
			Pathway,
			Wall
		};

		PlayFieldGridComponent(amu::GameObject* ownerObjectPtr, int rowsGrid, int colsGrid);
		virtual ~PlayFieldGridComponent() override = default;

		PlayFieldGridComponent(PlayFieldGridComponent const& other) = delete;
		PlayFieldGridComponent(PlayFieldGridComponent&& other) = delete;
		PlayFieldGridComponent& operator=(PlayFieldGridComponent const& other) = delete;
		PlayFieldGridComponent& operator=(PlayFieldGridComponent&& other) = delete;

		void SetElement(std::int64_t const& rowIdx, std::int64_t const& colIdx, std::string_view const& typeString);

	private:
		std::int64_t const m_RowsGrid{};
		std::int64_t const m_ColsGrid{};
		std::vector<TileType> m_TileVec{};

		[[nodiscard]] std::int64_t GetIndex(std::int64_t const& rowIdx, std::int64_t const& colIdx) const;
	};

}

#endif