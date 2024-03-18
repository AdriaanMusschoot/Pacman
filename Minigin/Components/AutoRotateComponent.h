#pragma once
#include "Base/Component.h"
#include "TransformComponent.h"
#include "glm/vec3.hpp"

namespace amu
{

	class AutoRotateComponent final : public amu::Component
	{
	public:
		explicit AutoRotateComponent(amu::GameObject* ownerObjectPtr, int radius, double speed, double angle);
		explicit AutoRotateComponent(amu::GameObject* ownerObjectPtr);
		~AutoRotateComponent() override = default;
	
		AutoRotateComponent(const AutoRotateComponent& other) = delete;
		AutoRotateComponent(AutoRotateComponent&& other) = delete;
		AutoRotateComponent& operator=(const AutoRotateComponent& other) = delete;
		AutoRotateComponent& operator=(AutoRotateComponent&& other) = delete;
	
		void Update() override;
	private:
		glm::vec2 m_CenterPosition{ 0, 0 };

		int m_Radius = 0;
		double m_Speed = 2;

		double m_Angle = 0;

		TransformComponent* m_TransformPtr = nullptr;
	};

}
