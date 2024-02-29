#pragma once
#include <memory>
#include <vector>

#include "Component.h"

namespace dae
{
	class GameObject final
	{
	public:
		GameObject()
			: m_ComponentUPtrVec{}
			, m_ToBeDestroyed{ false }
		{
		}
		~GameObject() = default;
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void Update();
		void Render() const;

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
				//moves element to be removed to the back 
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

		void EnableToBeDestroyed() { m_ToBeDestroyed = true; }
		bool GetToBeDestroyed() const { return m_ToBeDestroyed; }

	private:
		std::vector<std::unique_ptr<Component>> m_ComponentUPtrVec;

		bool m_ToBeDestroyed;
	};

	
}
