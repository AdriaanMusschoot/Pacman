#ifndef PM_PLAYSOUND_COMMAND_H
#define PM_PLAYSOUND_COMMAND_H

#include "Command.h"

namespace pacman
{

	class PlaySoundCommand final : public amu::Command
	{
	public:
		PlaySoundCommand() {}
		~PlaySoundCommand() = default;

		PlaySoundCommand(const PlaySoundCommand& other) = delete;
		PlaySoundCommand(PlaySoundCommand&& other) = delete;
		PlaySoundCommand& operator=(const PlaySoundCommand& other) = delete;
		PlaySoundCommand& operator=(PlaySoundCommand&& other) = delete;

		void Execute() override;
	private:

	};
}

#endif //PM_PLAYSOUND_COMMAND_H