#pragma once
#include "Transform.h"

namespace dae
{
	class GameObject;
}

class Component
{
public:
	Component() = default;
	virtual ~Component() = default;

	Component(const Component& other) = delete;
	Component(Component&& other) = delete;
	Component& operator=(const Component& other) = delete;
	Component& operator=(Component&& other) = delete;

	virtual void Update() {}
	virtual void Render() const {}

	void SetPosition(float x, float y, float z = 0);
protected:
	dae::Transform m_Transform;
};