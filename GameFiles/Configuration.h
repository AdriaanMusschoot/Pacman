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

		struct SoundRequest
		{
			SoundId Id;
			std::string FilePath;
			int Volume;
			int Loops;
		};

		SoundRequest const PACMAN_CHOMP{ 0, "Sounds/PacmanChomp.wav", 10, -1 };
		SoundRequest const PACMAN_DEATH{ 1, "Sounds/PacmanDeath.wav", 10, 0 };

	}

	namespace collision
	{

		using CollisionType = int;

		CollisionType const PacmanEatSmall{ 0 };

	}
}

#endif