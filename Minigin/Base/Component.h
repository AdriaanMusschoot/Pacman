#pragma once
#include <memory>

namespace amu
{

	class GameObject;

	class Component
	{
	public:
		virtual ~Component() = default;
	
		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;
	
	protected:
		explicit Component(GameObject * ownerObjectPtr)
			: m_OwnerGameObjectPtr{ ownerObjectPtr }
			, m_ToBeDestroyed{ false }
		{
		}
	
		virtual void Update() {}
		virtual void Render() const {}

		GameObject* GetOwnerGameObject() const { return m_OwnerGameObjectPtr; }

		void EnableToBeDestroyed() { m_ToBeDestroyed = true; }
		bool GetToBeDestroyed() const { return m_ToBeDestroyed; }
	private:
		friend class GameObject;

		GameObject* m_OwnerGameObjectPtr = nullptr;

		bool m_ToBeDestroyed = false;
	};

}