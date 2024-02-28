#pragma once
#include <memory>
#include <vector>

#include "Component.h"
#include "TransformComponent.h"

namespace dae
{
	class Texture2D;
	class GameObject final
	{
		TransformComponent m_transform{};

		std::vector<std::unique_ptr<Component>> m_ComponentUPtrVec;
	public:
		void Update();
		void Render() const;

		void SetPosition(float x, float y);

		template <typename T, typename... Args>
		void AddComponent(Args&&... args)
		{
			m_ComponentUPtrVec.emplace_back(std::make_unique<T>(std::forward<Args>(args)...));
		}

		template <typename T>
		void RemoveComponent()
		{
			//erase removes element from start iterator (given by remove_if) to end iterator
			m_ComponentUPtrVec.erase
			(
				//moves elements to be removed to the back 
				std::remove_if(m_ComponentUPtrVec.begin(), m_ComponentUPtrVec.end(),
					[](const auto& component)
					{
						return dynamic_cast<T*>(component.get()) != nullptr;
					}),
				m_ComponentUPtrVec.end()
			);
		}

		template <typename T> 
		T* GetComponent()
		{
			for (const auto& component : m_ComponentUPtrVec)
			{
				if (const auto neededComponent = dynamic_cast<T*>(component.get()); neededComponent != nullptr)
				{
					return neededComponent;
				}
			}
			return nullptr;
		}

		template <typename T>
		bool ComponentAdded() const
		{
			for (const auto& component : m_ComponentUPtrVec)
			{
				if (const auto neededComponent = dynamic_cast<T*>(component.get()); neededComponent != nullptr)
				{
					return true;
				}
			}
			return false;
		}

		GameObject() = default;
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;
	};
}
