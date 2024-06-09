#ifndef PM_START_GAME_COMMAND_H
#define PM_START_GAME_COMMAND_H
#include "Configuration.h"
#include "GameObjectCommands.h"
#include "Components/PacmanFSM.h"

namespace pacman
{

	class StartGameCommand final : public amu::Command
	{
	public:
		StartGameCommand() = default;
		virtual ~StartGameCommand() override = default;

		StartGameCommand(StartGameCommand const& other) = delete;
		StartGameCommand(StartGameCommand&& other) = delete;
		StartGameCommand& operator=(StartGameCommand const& other) = delete;
		StartGameCommand& operator=(StartGameCommand&& other) = delete;

		void Execute() override;
	private:
	};

}

#endif //PM_START_GAME_COMMAND_H