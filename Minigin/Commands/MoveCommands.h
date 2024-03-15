#pragma once
#include "GameActorCommands.h"

namespace amu
{

	class MoveRight final : public GameActorCommand
	{
	public:
		MoveRight(GameObject* actorPtr)
			: GameActorCommand(actorPtr)
		{
			m_MovementComponent = GetGameActor()->GetComponent<MoveableComponent>();
		}
		virtual ~MoveRight() = default;

		MoveRight(const MoveRight& other) = delete;
		MoveRight(MoveRight&& other) = delete;
		MoveRight& operator=(const MoveRight& other) = delete;
		MoveRight& operator=(MoveRight&& other) = delete;

		void Execute() override
		{
			m_MovementComponent->MoveRight();
		}
	private:
		MoveableComponent* m_MovementComponent{ nullptr };
	};
	
	class MoveLeft final : public GameActorCommand
	{
	public:
		MoveLeft(GameObject* actorPtr)
			: GameActorCommand(actorPtr)
		{
			m_MovementComponent = GetGameActor()->GetComponent<MoveableComponent>();
		}
		virtual ~MoveLeft() = default;

		MoveLeft(const MoveRight& other) = delete;
		MoveLeft(MoveRight&& other) = delete;
		MoveLeft& operator=(const MoveRight& other) = delete;
		MoveLeft& operator=(MoveRight&& other) = delete;

		void Execute() override
		{
			m_MovementComponent->MoveLeft();
		}
	private:
		MoveableComponent* m_MovementComponent{ nullptr };
	};

	class MoveUp final : public GameActorCommand
	{
	public:
		MoveUp(GameObject* actorPtr)
			: GameActorCommand(actorPtr)
		{
			m_MovementComponent = GetGameActor()->GetComponent<MoveableComponent>();
		}
		virtual ~MoveUp() = default;

		MoveUp(const MoveUp& other) = delete;
		MoveUp(MoveUp&& other) = delete;
		MoveUp& operator=(const MoveUp& other) = delete;
		MoveUp& operator=(MoveUp&& other) = delete;

		void Execute() override
		{
			m_MovementComponent->MoveUp();
		}
	private:
		MoveableComponent* m_MovementComponent{ nullptr };
	};

	class MoveDown final : public GameActorCommand
	{
	public:
		MoveDown(GameObject* actorPtr)
			: GameActorCommand(actorPtr)
		{
			m_MovementComponent = GetGameActor()->GetComponent<MoveableComponent>();
		}
		virtual ~MoveDown() = default;

		MoveDown(const MoveDown& other) = delete;
		MoveDown(MoveDown&& other) = delete;
		MoveDown& operator=(const MoveDown& other) = delete;
		MoveDown& operator=(MoveDown&& other) = delete;

		void Execute() override
		{
			m_MovementComponent->MoveDown();
		}
	private:
		MoveableComponent* m_MovementComponent{ nullptr };
	};
}