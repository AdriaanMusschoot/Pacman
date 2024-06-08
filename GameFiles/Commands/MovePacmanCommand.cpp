#include "MovePacmanCommand.h"

pacman::MovePacmanCommand::MovePacmanCommand(amu::GameObject* gameObjectPtr, glm::vec2 const& direction)
	: GameObjectCommand(gameObjectPtr)
	, m_Direction{ direction }
	, m_PacmanFSM{ GetGameObject()->GetComponent<PacmanFSMComponent>() }
{
}

void pacman::MovePacmanCommand::Execute()
{
	if (m_PacmanFSM)
	{
		m_PacmanFSM->HandleInput(m_Direction);
	}
}