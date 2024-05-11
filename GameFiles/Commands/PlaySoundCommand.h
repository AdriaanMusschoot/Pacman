#ifndef PM_PLAYSOUND_COMMAND_H
#define PM_PLAYSOUND_COMMAND_H

#include "Command.h"

namespace amu
{

	class PlayPacmanChomp final : public amu::Command
	{
	public:
		PlayPacmanChomp() = default;
		virtual ~PlayPacmanChomp() override = default;

		PlayPacmanChomp(PlayPacmanChomp const& other) = delete;
		PlayPacmanChomp(PlayPacmanChomp&& other) = delete;
		PlayPacmanChomp& operator=(PlayPacmanChomp const& other) = delete;
		PlayPacmanChomp& operator=(PlayPacmanChomp&& other) = delete;

		void Execute() override;
	private:

	};

	class PlayPacmanDeath final : public amu::Command
	{
	public:
		PlayPacmanDeath() = default;
		virtual ~PlayPacmanDeath() override = default;

		PlayPacmanDeath(PlayPacmanDeath const& other) = delete;
		PlayPacmanDeath(PlayPacmanDeath&& other) = delete;
		PlayPacmanDeath& operator=(PlayPacmanDeath const& other) = delete;
		PlayPacmanDeath& operator=(PlayPacmanDeath&& other) = delete;

		void Execute() override;
	private:

	};

}

#endif //PM_PLAYSOUND_COMMAND_H