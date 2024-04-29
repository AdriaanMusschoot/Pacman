#ifndef PM_GAMELOAD_H
#define PM_GAMELOAD_H

#include "Scene.h"
#include "SceneManager.h"

#include "Component.h"
#include "GameObject.h"

#include "RenderComponent.h"
#include "TextComponent.h"
#include "TransformComponent.h"
#include "ServiceLocator.h"
#include "SoundSystem.h"
#include "InputManager.h"

#include "Components/FPSComponent.h"
#include "Commands/PlaySoundCommand.h"
#include "Configuration.h"

namespace pacman
{

	void LoadGame(amu::Scene* scenePtr)
	{
		using SoundId = pacman::config::SoundId;
		using InpMan = amu::InputManager;

		auto& inputManager = InpMan::GetInstance();
	
		std::unique_ptr backgroundUPtr{ std::make_unique<amu::GameObject>() };
		backgroundUPtr->AddComponent<amu::TransformComponent>(backgroundUPtr.get(), glm::vec2{ 0, 0 });
		backgroundUPtr->AddComponent<amu::RenderComponent>(backgroundUPtr.get(), "background.tga");

		std::unique_ptr daeLogoUPtr{ std::make_unique<amu::GameObject>() };
		daeLogoUPtr->AddComponent<amu::TransformComponent>(daeLogoUPtr.get(), glm::vec2{ pacman::config::WIDTH / 2 - 103, pacman::config::HEIGHT / 2 - 24 });
		daeLogoUPtr->AddComponent<amu::RenderComponent>(daeLogoUPtr.get(), "logo.tga");
		daeLogoUPtr->SetParent(backgroundUPtr.get(), false);

		std::unique_ptr titleUPtr{ std::make_unique<amu::GameObject>() };
		titleUPtr->AddComponent<amu::TransformComponent>(titleUPtr.get(), glm::vec2{ 80, 20 });
		titleUPtr->AddComponent<amu::TextComponent>(titleUPtr.get(), "Programming 4 Assignment", "Lingua.otf", 36);
		titleUPtr->SetParent(backgroundUPtr.get(), false);

		std::unique_ptr fpsCounterUPtr{ std::make_unique<amu::GameObject>() };
		fpsCounterUPtr->AddComponent<amu::TransformComponent>(fpsCounterUPtr.get(), glm::vec2{ 0, 50 });
		fpsCounterUPtr->AddComponent<amu::TextComponent>(fpsCounterUPtr.get(), "60", "Lingua.otf", 36);
		fpsCounterUPtr->AddComponent<amu::FPSComponent>(fpsCounterUPtr.get());
		fpsCounterUPtr->SetParent(backgroundUPtr.get(), false);

		scenePtr->Add(std::move(backgroundUPtr));
		scenePtr->Add(std::move(daeLogoUPtr));
		scenePtr->Add(std::move(titleUPtr));
		scenePtr->Add(std::move(fpsCounterUPtr));

		std::unique_ptr controllerExplainedUPtr{ std::make_unique<amu::GameObject>() };
		controllerExplainedUPtr->AddComponent<amu::TransformComponent>(controllerExplainedUPtr.get(), glm::vec2{ 0 , 170 });
		controllerExplainedUPtr->AddComponent<amu::TextComponent>(controllerExplainedUPtr.get(), "Use W-key to play pacman chomp sound", "Lingua.otf", 20);

		std::unique_ptr keyboardExplainedUPtr{ std::make_unique<amu::GameObject>() };
		keyboardExplainedUPtr->AddComponent<amu::TransformComponent>(keyboardExplainedUPtr.get(), glm::vec2{ 0, 190 });
		keyboardExplainedUPtr->AddComponent<amu::TextComponent>(keyboardExplainedUPtr.get(), "Use A-key to play pacman death sound", "Lingua.otf", 20);

		scenePtr->Add(std::move(controllerExplainedUPtr));
		scenePtr->Add(std::move(keyboardExplainedUPtr));

		std::unique_ptr playChompCommand{ std::make_unique<pacman::PlayPacmanChomp>() };

		inputManager.AddCommandKeyboard(InpMan::Key::W, InpMan::InputState::Pressed, std::move(playChompCommand));

		std::unique_ptr playDeathCommand{ std::make_unique<pacman::PlayPacmanDeath>() };

		inputManager.AddCommandKeyboard(InpMan::Key::A, InpMan::InputState::Pressed, std::move(playDeathCommand));
	}

}

#endif