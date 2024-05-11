#include "MovePacmanCommand.h"

pacman::MovePacmanCommand::MovePacmanCommand(amu::GameObject* gameObjectPtr, std::shared_ptr<IMovementState> newStateSPtr)
	: GameObjectCommand(gameObjectPtr)
	, m_NewStateSPtr{ newStateSPtr }
	, m_GridMovementPtr{ GetGameObject()->GetComponent<GridMovementComponent>() }
{
}

void pacman::MovePacmanCommand::Execute()
{
	if (m_GridMovementPtr)
	{
		m_GridMovementPtr->ChangeMovementState(m_NewStateSPtr);
	}
}
