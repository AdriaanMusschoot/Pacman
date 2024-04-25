#pragma once
#include "Component.h"
#include "Observer.h"
#include "TextComponent.h"
#include "Subject.h"
#include "GameObject.h"

namespace amu
{

	class GameObject;

	class DisplayComponent final : public Component, public Observer
	{
	public:
		DisplayComponent(GameObject * gameObjectPtr, const std::string & textToDisplay);
		virtual ~DisplayComponent() override = default;

		DisplayComponent(const DisplayComponent& other) = delete;
		DisplayComponent(DisplayComponent&& other) = delete;
		DisplayComponent& operator=(const DisplayComponent& other) = delete;
		DisplayComponent& operator=(DisplayComponent&& other) = delete;

		virtual void Notify(EventType eventType, Subject* subjectPtr) override;
		virtual void NotifyDestruction() override;
	private:
		std::string m_TextToDisplay{ "Text" };

		TextComponent* m_TextComponentPtr;
	};

}