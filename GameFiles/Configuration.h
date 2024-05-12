#ifndef PM_CONFIGURATION_H
#define PM_CONFIGURATION_H
#include <memory>
#include <fstream>
#include <regex>
#include <vector>
#include <iostream>
#include <execution>

namespace pacman
{

	namespace config
	{

		int constexpr SCALE_FACTOR{ 3 };
					  
		int constexpr WINDOW_WIDTH{ 224 * SCALE_FACTOR };
		int constexpr WINDOW_HEIGHT{ 248 * SCALE_FACTOR };
					  
		int constexpr ROWS_GRID{ 31 };
		int constexpr COLS_GRID{ 28 };
					  
		int constexpr CELL_WIDTH{ WINDOW_WIDTH / COLS_GRID };
		int constexpr CELL_HEIGHT{ WINDOW_HEIGHT / ROWS_GRID };

	}

	namespace sound
	{

		using SoundId = int;

		std::pair<SoundId, std::string> const PACMAN_DEATH{ std::make_pair<SoundId, std::string>(0, "Sounds/PacmanChomp.wav") };
		std::pair<SoundId, std::string> const PACMAN_CHOMP{ std::make_pair<SoundId, std::string>(1, "Sounds/PacmanDeath.wav") };

	}

	namespace collision
	{

		using CollisionType = int;

		CollisionType const PacmanEatSmall{ 0 };

	}
}

#endif