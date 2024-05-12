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
		MovePacmanCommand(amu::GameObject* gameObjectPtr, glm::vec2 const& direction);
		virtual ~MovePacmanCommand() override = default;

		MovePacmanCommand(MovePacmanCommand const& other) = delete;
		MovePacmanCommand(MovePacmanCommand&& other) = delete;
		MovePacmanCommand& operator=(MovePacmanCommand const& other) = delete;
		MovePacmanCommand& operator=(MovePacmanCommand&& other) = delete;

		void Execute() override;
	private:
		GridMovementComponent* m_GridMovementPtr{ nullptr };
		glm::vec2 m_Direction{ 0, 0 };
	};

}

#endif //PM_MOVE_PACMAN_COMMAND_H