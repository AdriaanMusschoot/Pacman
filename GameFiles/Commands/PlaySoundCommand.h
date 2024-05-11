#ifndef PM_PLAYSOUND_COMMAND_H
#define PM_PLAYSOUND_COMMAND_H

#include "Command.h"

namespace pacman
{

	class PlayPacmanChomp final : public pacman::Command
	{
	public:
		PlayPacmanChomp() {}
		~PlayPacmanChomp() = default;

		PlayPacmanChomp(const PlayPacmanChomp& other) = delete;
		PlayPacmanChomp(PlayPacmanChomp&& other) = delete;
		PlayPacmanChomp& operator=(const PlayPacmanChomp& other) = delete;
		PlayPacmanChomp& operator=(PlayPacmanChomp&& other) = delete;

		void Execute() override;
	private:

	};

	class PlayPacmanDeath final : public pacman::Command
	{
	public:
		PlayPacmanDeath() {}
		~PlayPacmanDeath() = default;

		PlayPacmanDeath(const PlayPacmanDeath& other) = delete;
		PlayPacmanDeath(PlayPacmanDeath&& other) = delete;
		PlayPacmanDeath& operator=(const PlayPacmanDeath& other) = delete;
		PlayPacmanDeath& operator=(PlayPacmanDeath&& other) = delete;

		void Execute() override;
	private:

	};

}

#endif //PM_PLAYSOUND_COMMAND_H