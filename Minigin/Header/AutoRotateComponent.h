#pragma once
#include "Component.h"
#include "TransformComponent.h"
#include "glm/vec3.hpp"

namespace amu
{

	class AutoRotateComponent final : public amu::Component
	{
	public:
		explicit AutoRotateComponent(const std::shared_ptr<amu::GameObject>& ownerObjectSPtr);
		explicit AutoRotateComponent(const std::shared_ptr<amu::GameObject>& ownerObjectSPtr, int radius, double speed);
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

		TransformComponent* m_ParentTransformPtr{ nullptr };
		TransformComponent* m_TransformPtr{ nullptr };
	};

}
