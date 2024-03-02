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
		explicit Component(const std::shared_ptr<GameObject>& ownerGameObjectSPtr)
			: m_OwnerGameObjectPtr{ ownerGameObjectSPtr.get() }
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

		GameObject* m_OwnerGameObjectPtr;

		bool m_ToBeDestroyed;
	};

}