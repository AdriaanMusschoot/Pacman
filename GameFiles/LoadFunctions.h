#ifndef PM_GAMELOAD_H
#define PM_GAMELOAD_H

#include "Scene.h"
#include "SceneManager.h"

#include "Component.h"
#include "GameObject.h"

#include "ServiceLocator.h"
#include "SoundSystem.h"
#include "InputManager.h"

#include "RenderComponent.h"
#include "TextComponent.h"
#include "TransformComponent.h"
#include "CollisionComponent.h"

#include "Components/PlayFieldGridComponent.h"
#include "Components/FPSComponent.h"
#include "Components/GridMovementComponent.h"

#include "Commands/PlaySoundCommand.h"
#include "Commands/MovePacmanCommand.h"

#include "Observers/SmallPickupObserver.h"

#include "Configuration.h"

namespace pacman
{

	void SpawnSmallPickup(amu::CollisionComponent* pacman, amu::Scene* scenePtr, std::int64_t const& row, std::int64_t const& col)
	{
		using namespace config;
		std::unique_ptr pickupSmallUPtr{ std::make_unique<amu::GameObject>() };
		pickupSmallUPtr->SetTag("PickupSmall");
		pickupSmallUPtr->AddComponent<amu::TransformComponent>(pickupSmallUPtr.get(), glm::vec2{ col * CELL_WIDTH + CELL_WIDTH / 2, row * CELL_HEIGHT + CELL_HEIGHT / 2 });
		pickupSmallUPtr->AddComponent<amu::RenderComponent>(pickupSmallUPtr.get(), "Sprites/EatableSmall.png");
		pacman->AddObserver(new SmallPickupObserver());
		scenePtr->Add(std::move(pickupSmallUPtr));
	}

	void SpawnBigPickup(amu::CollisionComponent*, amu::Scene* scenePtr, std::int64_t const& row, std::int64_t const& col)
	{
		using namespace config;
		std::unique_ptr pickupBigUPtr{ std::make_unique<amu::GameObject>() };
		pickupBigUPtr->SetTag("PickupBig");
		pickupBigUPtr->AddComponent<amu::TransformComponent>(pickupBigUPtr.get(), glm::vec2{ col * CELL_WIDTH + CELL_WIDTH / 2, row * CELL_HEIGHT + CELL_HEIGHT / 2 });
		pickupBigUPtr->AddComponent<amu::RenderComponent>(pickupBigUPtr.get(), "Sprites/EatableBig.png");
		scenePtr->Add(std::move(pickupBigUPtr));
	}

	amu::CollisionComponent* LoadPacman(amu::Scene* scenePtr, PlayFieldGridComponent* playFieldGridPtr, float x, float y)
	{
		using InpMan = amu::InputManager;
		auto& inputManager = InpMan::GetInstance();

		std::unique_ptr pacmanUPtr{ std::make_unique<amu::GameObject>() };
		pacmanUPtr->SetTag("Pacman");
		pacmanUPtr->AddComponent<amu::TransformComponent>(pacmanUPtr.get(), glm::vec2{ x, y });
		pacmanUPtr->AddComponent<amu::RenderComponent>(pacmanUPtr.get(), "Sprites/Pacman.png");
		pacmanUPtr->AddComponent<amu::CollisionComponent>(pacmanUPtr.get(), "PickupSmall", pacman::collision::PacmanEatSmall);
		pacmanUPtr->AddComponent<GridMovementComponent>(pacmanUPtr.get(), playFieldGridPtr, 100);

		std::unique_ptr upCommandUPtr{ std::make_unique<MovePacmanCommand>(pacmanUPtr.get(), glm::vec2{ 0, -1 })};
		inputManager.AddCommandKeyboard(InpMan::Key::W, InpMan::InputState::Pressed, std::move(upCommandUPtr));

		std::unique_ptr downCommandUPtr{ std::make_unique<MovePacmanCommand>(pacmanUPtr.get(), glm::vec2{ 0, 1 }) };
		inputManager.AddCommandKeyboard(InpMan::Key::S, InpMan::InputState::Pressed, std::move(downCommandUPtr));

		std::unique_ptr leftCommandUPtr{ std::make_unique<MovePacmanCommand>(pacmanUPtr.get(), glm::vec2{ -1, 0 }) };
		inputManager.AddCommandKeyboard(InpMan::Key::A, InpMan::InputState::Pressed, std::move(leftCommandUPtr));

		std::unique_ptr rightCommandUPtr{ std::make_unique<MovePacmanCommand>(pacmanUPtr.get(), glm::vec2{ 1, 0 }) };
		inputManager.AddCommandKeyboard(InpMan::Key::D, InpMan::InputState::Pressed, std::move(rightCommandUPtr));

		amu::CollisionComponent* temp{ pacmanUPtr->GetComponent<amu::CollisionComponent>() };

		scenePtr->Add(std::move(pacmanUPtr));

		return temp;
	}

	void PopulatePlayingGrid(amu::Scene* scenePtr)
	{
		using namespace config;
		std::unique_ptr gridLayoutUPtr{ std::make_unique<amu::GameObject>() };
		gridLayoutUPtr->AddComponent<PlayFieldGridComponent>(gridLayoutUPtr.get(), ROWS_GRID, COLS_GRID, CELL_HEIGHT, CELL_WIDTH);
		auto* gridLayoutComponent = gridLayoutUPtr->GetComponent<PlayFieldGridComponent>();

		std::ifstream gridLayoutFile("Resources/Files/GridLayout.csv");
		if (not gridLayoutFile.is_open())
		{
			throw std::runtime_error("failed to locate pickup positions");
		}
		//do not use until after while loop
		std::regex const validLineExpression("(\\d+),(\\d+),(\\d+),(\\w+),(\\w+)");
		std::smatch matches{};
		std::string line{};

		amu::CollisionComponent* pacmanCollider{ LoadPacman(scenePtr, gridLayoutComponent, 36, 36) };

		while (std::getline(gridLayoutFile, line))
		{
			if (std::regex_match(line, matches, validLineExpression))
			{
				//ignoring first match since its entire string in the capture group always
				//ignoring second match since its the index to generate col and row idx
				const std::int64_t rowIdx{ std::stoi(matches[2].str()) };
				const std::int64_t colIdx{ std::stoi(matches[3].str()) };

				//set the tile type
				gridLayoutComponent->SetTileType(rowIdx, colIdx, matches[4].str());

				//if the tile type was either of these nothing to do
				if (matches[4] == "wall" || matches[4] == "void")
				{
					continue;
				}

				//if none found nothing to do
				if (matches[5] == "none")
				{
					continue;
				}

				//if small spawn small pickup 
				if (matches[5] == "small")
				{
					SpawnSmallPickup(pacmanCollider, scenePtr, rowIdx, colIdx);
				}

				//if big spawn big pickup
				else if (matches[5] == "big")
				{
					SpawnBigPickup(pacmanCollider, scenePtr, rowIdx, colIdx);
				}
			}
			else
			{
				std::cout << "Invalid line: " << line << "\n";
			}
		}

		scenePtr->Add(std::move(gridLayoutUPtr));
	}

	void LoadMainScene(amu::Scene* scenePtr)
	{
		using SoundId = pacman::sound::SoundId;
		using InpMan = amu::InputManager;

		std::unique_ptr backgroundUPtr{ std::make_unique<amu::GameObject>() };
		backgroundUPtr->AddComponent<amu::TransformComponent>(backgroundUPtr.get(), glm::vec2{ pacman::config::WINDOW_WIDTH / 2, pacman::config::WINDOW_HEIGHT / 2 });
		backgroundUPtr->AddComponent<amu::RenderComponent>(backgroundUPtr.get(), "Sprites/PlayingField.png");

		std::unique_ptr fpsCounterUPtr{ std::make_unique<amu::GameObject>() };
		fpsCounterUPtr->AddComponent<amu::TransformComponent>(fpsCounterUPtr.get(), glm::vec2{ 50 , 50 });
		fpsCounterUPtr->AddComponent<amu::TextComponent>(fpsCounterUPtr.get(), "60", "Fonts/Lingua.otf", 36);
		fpsCounterUPtr->AddComponent<FPSComponent>(fpsCounterUPtr.get());

		scenePtr->Add(std::move(backgroundUPtr));

		PopulatePlayingGrid(scenePtr);

		scenePtr->Add(std::move(fpsCounterUPtr));
	}

}

#endif