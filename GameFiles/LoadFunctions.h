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
#include "Components/PlayFieldGridComponent.h"
#include "Components/FPSComponent.h"
#include "Commands/PlaySoundCommand.h"
#include "Configuration.h"

namespace pacman
{

	void SpawnSmallPickup(amu::Scene* scenePtr, std::int64_t const& row, std::int64_t const& col)
	{
		using namespace pacman::config;
		std::unique_ptr pickupSmallUPtr{ std::make_unique<amu::GameObject>() };
		pickupSmallUPtr->AddComponent<amu::TransformComponent>(pickupSmallUPtr.get(), glm::vec2{ col * CELL_WIDTH, row * CELL_HEIGHT });
		pickupSmallUPtr->AddComponent<amu::RenderComponent>(pickupSmallUPtr.get(), "Sprites/EatableSmall.png");
		scenePtr->Add(std::move(pickupSmallUPtr));
	}

	void SpawnBigPickup(amu::Scene* scenePtr, std::int64_t const& row, std::int64_t const& col)
	{
		using namespace pacman::config;
		std::unique_ptr pickupBigUPtr{ std::make_unique<amu::GameObject>() };
		pickupBigUPtr->AddComponent<amu::TransformComponent>(pickupBigUPtr.get(), glm::vec2{ col * CELL_WIDTH, row * CELL_HEIGHT });
		pickupBigUPtr->AddComponent<amu::RenderComponent>(pickupBigUPtr.get(), "Sprites/EatableBig.png");
		scenePtr->Add(std::move(pickupBigUPtr));
	}

	void LoadGridLayout(amu::Scene* scenePtr)
	{
		using namespace pacman::config;
		std::unique_ptr gridLayoutUPtr{ std::make_unique<amu::GameObject>() };
		gridLayoutUPtr->AddComponent<pacman::PlayFieldGridComponent>(gridLayoutUPtr.get(), ROWS_GRID, COLS_GRID, CELL_HEIGHT, CELL_WIDTH);

		std::ifstream gridLayoutFile("Resources/Files/GridLayout.csv");
		if (not gridLayoutFile.is_open())
		{
			throw std::runtime_error("failed to locate pickup positions");
		}
		//do not use until after while loop
		std::regex validLineExpression("(\\d+),(\\d+),(\\d+),(\\w+),(\\w+)");
		std::smatch matches{};
		std::string line{};
		while (std::getline(gridLayoutFile, line))
		{
			if (std::regex_match(line, matches, validLineExpression))
			{
				//ignoring first match since its entire string in the capture group always
				//ignoring second match since its the index to generate col and row idx
				const std::int64_t row{ std::stoi(matches[2].str()) };
				const std::int64_t col{ std::stoi(matches[3].str()) };

				auto& gridLayoutComponent = *gridLayoutUPtr->GetComponent<pacman::PlayFieldGridComponent>();
				
				gridLayoutComponent.SetTileType(row, col, matches[4].str());

				if (matches[5] == "small")
				{
					SpawnSmallPickup(scenePtr, row, col);
				}
				if (matches[5] == "big")
				{
					SpawnBigPickup(scenePtr, row, col);
				}
			}
		}

		scenePtr->Add(std::move(gridLayoutUPtr));
	}

	void LoadMainScene(amu::Scene* scenePtr)
	{
		using SoundId = pacman::sound::SoundId;
		using InpMan = amu::InputManager;

		auto& inputManager = InpMan::GetInstance();

		std::unique_ptr backgroundUPtr{ std::make_unique<amu::GameObject>() };
		backgroundUPtr->AddComponent<amu::TransformComponent>(backgroundUPtr.get(), glm::vec2{ 0, 0 });
		backgroundUPtr->AddComponent<amu::RenderComponent>(backgroundUPtr.get(), "Sprites/PlayingField.png");

		std::unique_ptr fpsCounterUPtr{ std::make_unique<amu::GameObject>() };
		fpsCounterUPtr->AddComponent<amu::TransformComponent>(fpsCounterUPtr.get(), glm::vec2{ 0, 50 });
		fpsCounterUPtr->AddComponent<amu::TextComponent>(fpsCounterUPtr.get(), "60", "Fonts/Lingua.otf", 36);
		fpsCounterUPtr->AddComponent<pacman::FPSComponent>(fpsCounterUPtr.get());

		scenePtr->Add(std::move(backgroundUPtr));

		LoadGridLayout(scenePtr);

		scenePtr->Add(std::move(fpsCounterUPtr));

		std::unique_ptr playChompCommand{ std::make_unique<amu::PlayPacmanChomp>() };

		inputManager.AddCommandKeyboard(InpMan::Key::W, InpMan::InputState::Pressed, std::move(playChompCommand));

		std::unique_ptr playDeathCommand{ std::make_unique<amu::PlayPacmanDeath>() };

		inputManager.AddCommandKeyboard(InpMan::Key::A, InpMan::InputState::Pressed, std::move(playDeathCommand));
	}

}

#endif