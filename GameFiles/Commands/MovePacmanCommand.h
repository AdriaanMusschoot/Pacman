#ifndef PM_MOVE_PACMAN_COMMAND_H
#define PM_MOVE_PACMAN_COMMAND_H
#include "Configuration.h"
#include "GameObjectCommands.h"
#include "Components/GridMovementComponent.h"

namespace pacman
{

	class MovePacmanCommand final : public amu::GameObjectCommand
	{
	public:
		MovePacmanCommand(amu::GameObject* gameObjectPtr, std::shared_ptr<IMovementState> newStateSPtr);
		virtual ~MovePacmanCommand() override = default;

		MovePacmanCommand(MovePacmanCommand const& other) = delete;
		MovePacmanCommand(MovePacmanCommand&& other) = delete;
		MovePacmanCommand& operator=(MovePacmanCommand const& other) = delete;
		MovePacmanCommand& operator=(MovePacmanCommand&& other) = delete;

		void Execute() override;
	private:
		std::shared_ptr<IMovementState> m_NewStateSPtr{ std::make_shared<IMovementState>() };
		GridMovementComponent* m_GridMovementPtr{ nullptr };
	};

}

#endif //PM_MOVE_PACMAN_COMMAND_H