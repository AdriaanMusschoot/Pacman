#include "MovePacmanCommand.h"

pacman::MovePacmanCommand::MovePacmanCommand(amu::GameObject* gameObjectPtr, glm::vec2 const& direction)
	: GameObjectCommand(gameObjectPtr)
	, m_Direction{ direction }
	, m_GridMovementPtr{ GetGameObject()->GetComponent<GridMovementComponent>() }
{
}

void pacman::MovePacmanCommand::Execute()
{
	if (m_GridMovementPtr)
	{
		m_GridMovementPtr->ChangeMovementState(m_Direction);
	}
}
