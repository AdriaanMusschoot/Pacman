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

	void LoadGridLayout(amu::Scene* scenePtr)
	{
		std::ifstream gridLayoutFile("Resources/Files/GridLayout.txt");

		if (not gridLayoutFile.is_open())
		{
			throw std::runtime_error("failed to locate pickup positions");
		}

		std::regex validLineExpression("(\\d+),(\\d+)\\s+(\\S+)");
		std::smatch matches{};
		std::string line;
		while (std::getline(gridLayoutFile, line))
		{
			if (std::regex_match(line, matches, validLineExpression))
			{
				//ignoring first match since its entire string in the capture group always
				int row{ std::stoi(matches[1].str()) };
				int col{ std::stoi(matches[2].str()) };


				std::unique_ptr pickupUPtr{ std::make_unique<amu::GameObject>() };
				pickupUPtr->AddComponent<amu::TransformComponent>(pickupUPtr.get(), glm::vec2{ col * pacman::config::CELL_WIDTH, row * pacman::config::CELL_HEIGHT });
				pickupUPtr->AddComponent<amu::RenderComponent>(pickupUPtr.get(), "Sprites/Eatable.png");

				scenePtr->Add(std::move(pickupUPtr));
			}
		}
	}

	void LoadGame(amu::Scene* scenePtr)
	{
		using SoundId = pacman::config::SoundId;
		using InpMan = amu::InputManager;

		auto& inputManager = InpMan::GetInstance();

		std::unique_ptr backgroundUPtr{ std::make_unique<amu::GameObject>() };
		backgroundUPtr->AddComponent<amu::TransformComponent>(backgroundUPtr.get(), glm::vec2{ 0, 0 });
		backgroundUPtr->AddComponent<amu::RenderComponent>(backgroundUPtr.get(), "Sprites/PlayingField.png");

		std::unique_ptr fpsCounterUPtr{ std::make_unique<amu::GameObject>() };
		fpsCounterUPtr->AddComponent<amu::TransformComponent>(fpsCounterUPtr.get(), glm::vec2{ 0, 50 });
		fpsCounterUPtr->AddComponent<amu::TextComponent>(fpsCounterUPtr.get(), "60", "Fonts/Lingua.otf", 36);
		fpsCounterUPtr->AddComponent<amu::FPSComponent>(fpsCounterUPtr.get());

		scenePtr->Add(std::move(backgroundUPtr));
		scenePtr->Add(std::move(fpsCounterUPtr));

		LoadGridLayout(scenePtr);

		std::unique_ptr playChompCommand{ std::make_unique<pacman::PlayPacmanChomp>() };

		inputManager.AddCommandKeyboard(InpMan::Key::W, InpMan::InputState::Pressed, std::move(playChompCommand));

		std::unique_ptr playDeathCommand{ std::make_unique<pacman::PlayPacmanDeath>() };

		inputManager.AddCommandKeyboard(InpMan::Key::A, InpMan::InputState::Pressed, std::move(playDeathCommand));
	}

}

#endif