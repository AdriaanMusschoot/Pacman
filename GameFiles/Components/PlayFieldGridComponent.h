#ifndef PM_PLAY_FIELD_GRID_H
#define PM_PLAY_FIELD_GRID_H

#include "Configuration.h"
#include "Component.h"

namespace amu
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
		PlayFieldGridComponent(amu::GameObject* ownerObjectPtr);
		virtual ~PlayFieldGridComponent() override = default;

		PlayFieldGridComponent(PlayFieldGridComponent const& other) = delete;
		PlayFieldGridComponent(PlayFieldGridComponent&& other) = delete;
		PlayFieldGridComponent& operator=(PlayFieldGridComponent const& other) = delete;
		PlayFieldGridComponent& operator=(PlayFieldGridComponent&& other) = delete;
	private:
		std::vector<TileType> TILE_VEC{ pacman::config::ROWS_GRID * pacman::config::COLS_GRID };
	};

}

#endif