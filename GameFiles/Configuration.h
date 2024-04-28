#ifndef PM_SOUNDIDS_H
#define PM_SOUNDIDS_H

namespace pacman
{

	namespace config
	{

		enum class SoundId
		{
			PacmanDeath,
			PacmanChomp
		};

		constexpr int WIDTH{ 224 * 3 };
		constexpr int HEIGHT{ 288 * 3 };
	}

}

#endif