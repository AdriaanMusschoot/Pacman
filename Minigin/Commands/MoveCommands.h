#pragma once
#include "GameObjectCommands.h"
#include "Components/TransformComponent.h"

namespace amu
{

	class MoveCommand final : public GameObjectCommand
	{
	public:
		MoveCommand(GameObject* gameObjectPtr, glm::vec2 direction, double speed)
			: GameObjectCommand(gameObjectPtr)
			, m_DirectionVector{ direction }
			, m_Speed{ speed }
		{
			m_TransformComponentPtr = GetGameObject()->GetComponent<TransformComponent>();
		}
		virtual ~MoveCommand() = default;

		MoveCommand(const MoveCommand& other) = delete;
		MoveCommand(MoveCommand&& other) = delete;
		MoveCommand& operator=(const MoveCommand& other) = delete;
		MoveCommand& operator=(MoveCommand&& other) = delete;

		void Execute() override
		{
			m_TransformComponentPtr->Translate(
				glm::vec2{ 
					m_Speed * m_DirectionVector.x * GameTime::GetInstance().GetDeltaTime(), 
					m_Speed * m_DirectionVector.y * GameTime::GetInstance().GetDeltaTime() 
				});
		}
	private:
		glm::vec2 m_DirectionVector = glm::vec2{ 1, 0 };
		double m_Speed = 20.0;
		TransformComponent* m_TransformComponentPtr{ nullptr };
	};
}