#pragma once
#include "Component.h"
#include "TransformComponent.h"
#include "glm/vec3.hpp"

namespace amu
{

	class AutoRotateComponent final : public amu::Component
	{
	public:
		explicit AutoRotateComponent(amu::GameObject* ownerObjectSPtr, int radius, double speed, double angle = 0);
		explicit AutoRotateComponent(amu::GameObject* ownerObjectSPtr);
		~AutoRotateComponent() override = default;
	
		AutoRotateComponent(const AutoRotateComponent& other) = delete;
		AutoRotateComponent(AutoRotateComponent&& other) = delete;
		AutoRotateComponent& operator=(const AutoRotateComponent& other) = delete;
		AutoRotateComponent& operator=(AutoRotateComponent&& other) = delete;
	
		void Update() override;
	private:
		glm::vec3 m_CenterPosition{ 0, 0, 0 };

		int m_Radius{ 10 };
		double m_Speed{ 2 };

		double m_Angle{ 0 };

		TransformComponent* m_TransformPtr{ nullptr };
	};

}
