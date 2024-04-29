#ifndef PM_SOUNDIDS_H
#define PM_SOUNDIDS_H
#include <memory>

namespace pacman
{

	namespace config
	{

		enum class SoundId
		{
			PacmanDeath,
			PacmanChomp
		};

		constexpr std::pair<SoundId, std::string> PACMAN_DEATH{ std::make_pair<SoundId, std::string>(SoundId::PacmanChomp, "PacmanChomp.wav") };
		constexpr std::pair<SoundId, std::string> PACMAN_CHOMP{ std::make_pair<SoundId, std::string>(SoundId::PacmanDeath, "PacmanDeath.wav") };


		constexpr int WIDTH{ 224 * 3 };
		constexpr int HEIGHT{ 288 * 3 };
	}

}

#endif