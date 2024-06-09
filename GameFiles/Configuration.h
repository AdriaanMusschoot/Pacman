#ifndef PM_CONFIGURATION_H
#define PM_CONFIGURATION_H
#include <memory>
#include <fstream>
#include <regex>
#include <vector>
#include <iostream>
#include <execution>
#include "IObserver.h"
#include <glm/glm.hpp>

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

		glm::vec2 const VEC_UP{ 0, -1 };
		glm::vec2 const VEC_DOWN{ 0, 1 };
		glm::vec2 const VEC_LEFT{ -1, 0 };
		glm::vec2 const VEC_RIGHT{ 1, 0 };
		glm::vec2 const VEC_NEUTRAL{ 0, 0 };
		glm::vec2 const VEC_INVALID{ -1, -1 };

		double constexpr MAX_TIME_PICKUP{ 10.0 };
		int constexpr RETURN_TO_SPAWN_SPEED{ 300 };
		int constexpr PACMAN_SPEED{ 180 };
		int constexpr GHOST_SPEED{ 150 };
	}

	namespace tags
	{

		std::string const PACMAN{ "Pacman" };
		std::string const PICKUP_SMALL{ "PickupSmall" };
		std::string const PICKUP_BIG{ "PickupBig" };
		std::string const GHOST{ "Ghost" };
		std::string const MAIN_SCENE{ "Pacman Scene" };
		std::string const MENU_SCENE{ "Menu Scene" };
		std::string const HIGHSCORE_SCENE{ "Highscore Scene" };

	}

	namespace events
	{

		amu::IObserver::Event constexpr GHOST_INPUT_REQUIRED{ 0 };
		amu::IObserver::Event constexpr PACMAN_EAT_SMALL_PICKUP{ 1 };
		amu::IObserver::Event constexpr PACMAN_EAT_BIG_PICKUP{ 2 };
		amu::IObserver::Event constexpr GRID_DIRECTION_CHANGES{ 3 };
		amu::IObserver::Event constexpr PACMAN_HIT_GHOST{ 4 };
		amu::IObserver::Event constexpr PACMAN_DYING_ANIM_FINISHED{ 5 };
		amu::IObserver::Event constexpr SMALL_PICKUP_VANISHED{ 6 };
		amu::IObserver::Event constexpr BIG_PICKUP_VANISHED{ 7 };
		amu::IObserver::Event constexpr GHOST_PANICK{ 8 };
		amu::IObserver::Event constexpr GHOST_ATTACK{ 9 };
		amu::IObserver::Event constexpr PACMAN_EAT_GHOST{ 10 };
		amu::IObserver::Event constexpr PACMAN_COLLECT{ 11 };
		amu::IObserver::Event constexpr GHOST_RUSHING_TO_SPAWN{ 12 };
		amu::IObserver::Event constexpr PACMAN_ATE_ALL{ 13 };

	}

	namespace resources
	{

		namespace sprites
		{

			struct SpriteData
			{
				std::string const FilePath;
				int const Rows;
				int const Cols;
			};

			SpriteData const PACMAN{ "Sprites/Pacman.png", 4, 14 };
			SpriteData const PICKUP_SMALL{ "Sprites/EatableSmall.png", 1, 1 };
			SpriteData const PICKUP_BIG{ "Sprites/EatableBig.png", 1, 1 };
			SpriteData const PLAYINGFIELD{ "Sprites/PlayingField.png", 1, 1 };
			SpriteData const BLINKY{ "Sprites/Blinky.png", 1, 16 };
			SpriteData const PINKY{ "Sprites/Pinky.png", 1, 16 };
			SpriteData const INKY{ "Sprites/Inky.png", 1, 16 };
			SpriteData const CLYDE{ "Sprites/Clyde.png", 1, 16 };

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
				std::string const GHOST_SPAWN{ "blinky" };
				std::string const PACMAN_SPAWN{ "spawn" };

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