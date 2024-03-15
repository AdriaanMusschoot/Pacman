#pragma once
#include "Base/Component.h"
#include "Base/GameObject.h"
#include "TransformComponent.h"

namespace amu
{

	class MoveableComponent final : public Component
	{
	public:
		MoveableComponent(GameObject* ownerObjectPtr, int speed);
		~MoveableComponent() override = default;

		MoveableComponent(const MoveableComponent& other) = delete;
		MoveableComponent(MoveableComponent&& other) = delete;
		MoveableComponent& operator=(const MoveableComponent& other) = delete;
		MoveableComponent& operator=(MoveableComponent&& other) = delete;

		void MoveRight();
		void MoveLeft();
		void MoveUp();
		void MoveDown();

	private:
		TransformComponent* m_TransformPtr;
		const int m_Speed;
	};

}