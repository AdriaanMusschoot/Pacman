#pragma once
#include <memory>

namespace dae
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
		explicit Component(const std::shared_ptr<GameObject>& parentGameObjectSPtr)
			: m_ParentGameObjectWPtr{ parentGameObjectSPtr.get() }
			, m_ToBeDestroyed{ false }
		{
		}
	
		virtual void Update() {}
		virtual void Render() const {}

		GameObject* GetParentGameObject() const { return m_ParentGameObjectWPtr; }

		void EnableToBeDestroyed() { m_ToBeDestroyed = true; }
		[[nodiscard]] bool GetToBeDestroyed() const { return m_ToBeDestroyed; }
	private:
		friend class GameObject;

		GameObject* m_ParentGameObjectWPtr;

		bool m_ToBeDestroyed;
	};

}