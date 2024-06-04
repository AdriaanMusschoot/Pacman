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

	namespace collision
	{

		using CollisionType = int;

		CollisionType const PACMAN_EAT_SMALL{ 0 };

	}

	namespace tags
	{

		std::string const PACMAN{ "Pacman" };
		std::string const PICKUP_SMALL{ "PickupSmall" };
		std::string const PICKUP_BIG{ "PickupBig" };
		std::string const BLINKY{ "Blinky" };

	}

	namespace resources
	{

		namespace sprites
		{

			std::string const PACMAN{ "Sprites/Pacman.png" };
			std::string const PICKUP_SMALL{ "Sprites/EatableSmall.png" };
			std::string const PICKUP_BIG{ "Sprites/EatableBig.png" };
			std::string const PLAYINGFIELD{ "Sprites/PlayingField.png" };
			std::string const BLINKY{ "Sprites/Blinky.png" };

		}

		namespace file
		{

			std::string const GRID_LAYOUT_CSV{ "Resources/Files/GridLayout.csv" };

			namespace regex
			{

				std::string const WALL{ "wall" };
				std::string const UNREACHABLE{ "void" };
				std::string const NOTHING_TO_SPAWN{ "none" };
				std::string const PICKUP_SMALL{ "small" };
				std::string const PICKUP_BIG{ "big" };
				std::string const BLINKY_SPAWN{ "blinky" };

			}

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

		namespace font
		{

			std::string const LINGUA{ "Fonts/Lingua.otf" };

		}
	}
}

#endif