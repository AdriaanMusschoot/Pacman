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

		constexpr int SCALE_FACTOR{ 3 };

		constexpr int WINDOW_WIDTH{ 224 * SCALE_FACTOR };
		constexpr int WINDOW_HEIGHT{ 248 * SCALE_FACTOR };

		constexpr int ROWS_GRID{ 31 };
		constexpr int COLS_GRID{ 28 };

		constexpr int CELL_WIDTH{ WINDOW_WIDTH / COLS_GRID };
		constexpr int CELL_HEIGHT{ WINDOW_HEIGHT / ROWS_GRID };

	}

	namespace sound
	{

		using SoundId = int;

		const std::pair<SoundId, std::string> PACMAN_DEATH{ std::make_pair<SoundId, std::string>(0, "Sounds/PacmanChomp.wav") };
		const std::pair<SoundId, std::string> PACMAN_CHOMP{ std::make_pair<SoundId, std::string>(1, "Sounds/PacmanDeath.wav") };

	}

}

#endif