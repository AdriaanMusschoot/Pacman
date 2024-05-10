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
		DisplayComponent(GameObject * gameObjectPtr, std::string_view const& textToDisplay);
		virtual ~DisplayComponent() override = default;

		DisplayComponent(DisplayComponent const& other) = delete;
		DisplayComponent(DisplayComponent&& other) = delete;
		DisplayComponent& operator=(DisplayComponent const& other) = delete;
		DisplayComponent& operator=(DisplayComponent&& other) = delete;

		void Notify(EventType eventType, Subject* subjectPtr) override;
		void NotifyDestruction() override;
	private:
		std::string m_TextToDisplay{ "Text" };

		TextComponent* m_TextComponentPtr;
	};

}