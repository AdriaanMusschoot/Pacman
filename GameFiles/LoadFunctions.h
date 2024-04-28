#ifndef PM_GAMELOAD_H
#define PM_GAMELOAD_H

#include "Scene.h"
#include "SceneManager.h"

#include "Component.h"
#include "GameObject.h"

#include "TextureComponent.h"
#include "TransformComponent.h"

#include "ServiceLocator.h"
#include "SoundSystem.h"
#include "InputManager.h"

#include "Commands/PlaySoundCommand.h"
#include "SoundIds.h"

namespace pacman
{

	void LoadGame(amu::Scene* scenePtr)
	{
		using SoundId = pacman::config::SoundId;
		using InpMan = amu::InputManager;
		using SerLoc = amu::ServiceLocator;

		std::unique_ptr titleUPtr{ std::make_unique<amu::GameObject>() };
	
		titleUPtr->AddComponent<amu::TransformComponent>(titleUPtr.get(), glm::vec2{ 0, 0 });
		titleUPtr->AddComponent<amu::RenderComponent>(titleUPtr.get(), "background.tga");
	
		scenePtr->Add(std::move(titleUPtr));

		SerLoc::GetInstance().GetSoundSystem()->AddSoundEffect(static_cast<int>(SoundId::PacManDeath), "PacManDeath.wav");

		std::unique_ptr playSoundCommand{ std::make_unique<pacman::PlaySoundCommand>() };

		InpMan::GetInstance().AddCommandKeyboard(InpMan::Key::W, InpMan::InputState::Pressed, std::move(playSoundCommand));
	}

}

#endif