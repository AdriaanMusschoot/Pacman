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
		Component(const std::shared_ptr<GameObject>& parentGameObjectSPtr)
			: m_ParentGameObjectWPtr{ parentGameObjectSPtr }
		{

		}
	
		virtual void Update() {}
		virtual void Render() const {}

		std::weak_ptr<GameObject> GetParentGameObject() const { return m_ParentGameObjectWPtr; }
	private:
		friend class GameObject;

		std::weak_ptr<GameObject> m_ParentGameObjectWPtr;
	};

}