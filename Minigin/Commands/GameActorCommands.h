#pragma once
#include "Command.h"
#include "Base/GameObject.h"
#include "Components/MoveableComponent.h"
#include "glm/glm.hpp"
#include "Singletons/Time.h"

namespace amu
{

	class GameActorCommand : public Command
	{
	public:
		GameActorCommand(GameObject* actorPtr)
			: m_ActorPtr{ actorPtr }
		{}
		virtual ~GameActorCommand() = default;

		GameActorCommand(const GameActorCommand& other) = delete;
		GameActorCommand(GameActorCommand&& other) = delete;
		GameActorCommand& operator=(const GameActorCommand& other) = delete;
		GameActorCommand& operator=(GameActorCommand&& other) = delete;
	protected:
		GameObject* GetGameActor() const { return m_ActorPtr; }
	private:
		GameObject* m_ActorPtr{ nullptr };
	};

}