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
#include "Components/BlinkyAIComponent.h"

#include "Colliders/PacmanCollider.h"
#include "Colliders/SmallPickupCollider.h"
#include "Colliders/BigPickupCollider.h"

#include "Commands/MovePacmanCommand.h"

#include "Animations/GhostAnimationComponent.h"
#include "Animations/PacmanAnimationComponent.h"

#include "Configuration.h"

namespace pacman
{

	void SpawnSmallPickup(amu::Scene* scenePtr, std::int64_t const& row, std::int64_t const& col)
	{
		using namespace config;
		std::unique_ptr pickupSmallUPtr{ std::make_unique<amu::GameObject>() };
		pickupSmallUPtr->SetTag(pacman::tags::PICKUP_SMALL);

		pickupSmallUPtr->AddComponent<amu::TransformComponent>(pickupSmallUPtr.get(), glm::vec2{ col * CELL_WIDTH + CELL_WIDTH / 2, row * CELL_HEIGHT + CELL_HEIGHT / 2 });

		amu::RenderComponent* renderComponentPtr{ pickupSmallUPtr->AddComponent<amu::RenderComponent>(pickupSmallUPtr.get(), resources::sprites::PICKUP_SMALL.FilePath) };
		renderComponentPtr->SetSourceRectangle(SDL_Rect{ 0, 0, renderComponentPtr->GetSize().x, renderComponentPtr->GetSize().y });

		pickupSmallUPtr->AddCollider(std::make_unique<SmallPickupCollider>(pickupSmallUPtr.get()));

		scenePtr->Add(std::move(pickupSmallUPtr));
	}

	void SpawnBigPickup(amu::Scene* scenePtr, std::int64_t const& row, std::int64_t const& col)
	{
		using namespace config;
		std::unique_ptr pickupBigUPtr{ std::make_unique<amu::GameObject>() };
		pickupBigUPtr->SetTag(pacman::tags::PICKUP_BIG);

		pickupBigUPtr->AddComponent<amu::TransformComponent>(pickupBigUPtr.get(), glm::vec2{ col * CELL_WIDTH + CELL_WIDTH / 2, row * CELL_HEIGHT + CELL_HEIGHT / 2 });

		amu::RenderComponent* renderComponentPtr{ pickupBigUPtr->AddComponent<amu::RenderComponent>(pickupBigUPtr.get(), resources::sprites::PICKUP_BIG.FilePath) };
		renderComponentPtr->SetSourceRectangle(SDL_Rect{ 0, 0, renderComponentPtr->GetSize().x, renderComponentPtr->GetSize().y });

		pickupBigUPtr->AddCollider(std::make_unique<BigPickupCollider>(pickupBigUPtr.get()));

		scenePtr->Add(std::move(pickupBigUPtr));
	}

	amu::GameObject* LoadPacman(amu::Scene* scenePtr, PlayFieldGridComponent* playFieldGridPtr, float x, float y)
	{
		using InpMan = amu::InputManager;
		auto& inputManager = InpMan::GetInstance();

		std::unique_ptr pacmanUPtr{ std::make_unique<amu::GameObject>() };
		pacmanUPtr->SetTag(pacman::tags::PACMAN);

		pacmanUPtr->AddComponent<amu::TransformComponent>(pacmanUPtr.get(), glm::vec2{ x, y });

		amu::RenderComponent* renderCompPtr{ pacmanUPtr->AddComponent<amu::RenderComponent>(pacmanUPtr.get(), resources::sprites::PACMAN.FilePath) };
		renderCompPtr->SetSourceRectangle(SDL_Rect{ 0, 0, renderCompPtr->GetSize().x / resources::sprites::PACMAN.Cols, renderCompPtr->GetSize().y / resources::sprites::PACMAN.Rows });
		PacmanAnimationComponent* pmAnimPtr{ pacmanUPtr->AddComponent<PacmanAnimationComponent>(pacmanUPtr.get()) };

		pacmanUPtr->AddCollider(std::make_unique<PacmanCollider>(pacmanUPtr.get()));

		GridMovementComponent* gridMovePtr{ pacmanUPtr->AddComponent<GridMovementComponent>(pacmanUPtr.get(), playFieldGridPtr, 100) };
		gridMovePtr->AddObserver(pmAnimPtr);

		std::unique_ptr upCommandUPtr{ std::make_unique<MovePacmanCommand>(pacmanUPtr.get(), config::VEC_UP)};
		inputManager.AddCommandKeyboard(InpMan::Key::W, InpMan::InputState::Pressed, std::move(upCommandUPtr));

		std::unique_ptr downCommandUPtr{ std::make_unique<MovePacmanCommand>(pacmanUPtr.get(), config::VEC_DOWN) };
		inputManager.AddCommandKeyboard(InpMan::Key::S, InpMan::InputState::Pressed, std::move(downCommandUPtr));

		std::unique_ptr leftCommandUPtr{ std::make_unique<MovePacmanCommand>(pacmanUPtr.get(), config::VEC_LEFT) };
		inputManager.AddCommandKeyboard(InpMan::Key::A, InpMan::InputState::Pressed, std::move(leftCommandUPtr));

		std::unique_ptr rightCommandUPtr{ std::make_unique<MovePacmanCommand>(pacmanUPtr.get(), config::VEC_RIGHT) };
		inputManager.AddCommandKeyboard(InpMan::Key::D, InpMan::InputState::Pressed, std::move(rightCommandUPtr));

		amu::GameObject* pacmanPtr{ scenePtr->Add(std::move(pacmanUPtr)) };

		return pacmanPtr;
	}

	void SpawnBlinky(amu::Scene* scenePtr, PlayFieldGridComponent* playFieldGridPtr, amu::GameObject* pacmanPtr, std::int64_t const& row, std::int64_t const& col)
	{
		using namespace config;

		std::unique_ptr blinkyUPtr{ std::make_unique<amu::GameObject>() };
		blinkyUPtr->SetTag(tags::BLINKY);

		blinkyUPtr->AddComponent<amu::TransformComponent>(blinkyUPtr.get(), glm::vec2{ col * CELL_WIDTH, row * CELL_HEIGHT + CELL_HEIGHT / 2 });

		amu::RenderComponent* renderCompPtr{ blinkyUPtr->AddComponent<amu::RenderComponent>(blinkyUPtr.get(), resources::sprites::BLINKY.FilePath) };
		renderCompPtr->SetSourceRectangle(SDL_Rect{ 0, 0, renderCompPtr->GetSize().x / resources::sprites::BLINKY.Cols, renderCompPtr->GetSize().y / resources::sprites::BLINKY.Rows });
		GhostAnimationComponent* animComponent{ blinkyUPtr->AddComponent<GhostAnimationComponent>(blinkyUPtr.get()) };

		GridMovementComponent* gridMoveCompPtr{ blinkyUPtr->AddComponent<GridMovementComponent>(blinkyUPtr.get(), playFieldGridPtr, 100) };
		BlinkyAIComponent* blinkyAIComponentPtr{ blinkyUPtr->AddComponent<BlinkyAIComponent>(blinkyUPtr.get(), pacmanPtr->GetComponent<amu::TransformComponent>()) };

		gridMoveCompPtr->AddObserver(blinkyAIComponentPtr);

		blinkyAIComponentPtr->AddObserver(animComponent);

		PacmanCollider* pmColliderPtr{ dynamic_cast<PacmanCollider*>(pacmanPtr->GetCollider()) };
		pmColliderPtr->AddObserver(blinkyUPtr->GetComponent<BlinkyAIComponent>());
		scenePtr->Add(std::move(blinkyUPtr));
	}

	void PopulatePlayingGrid(amu::Scene* scenePtr)
	{
		using namespace config;
		std::unique_ptr gridLayoutUPtr{ std::make_unique<amu::GameObject>() };
		gridLayoutUPtr->AddComponent<PlayFieldGridComponent>(gridLayoutUPtr.get(), ROWS_GRID, COLS_GRID, CELL_HEIGHT, CELL_WIDTH);
		auto* gridLayoutComponent = gridLayoutUPtr->GetComponent<PlayFieldGridComponent>();

		std::ifstream gridLayoutFile(resources::file::GRID_LAYOUT_CSV);
		if (not gridLayoutFile.is_open())
		{
			throw std::runtime_error("failed to locate grid layout positions");
		}
		//do not use until after while loop
		std::regex const validLineExpression("(\\d+),(\\d+),(\\d+),(\\w+),(\\w+)");
		std::smatch matches{};
		std::string line{};

		amu::GameObject* pacmanPtr{ LoadPacman(scenePtr, gridLayoutComponent, 36, 36) };

		while (std::getline(gridLayoutFile, line))
		{
			namespace rgx = resources::file::regex;
			if (std::regex_match(line, matches, validLineExpression))
			{
				//ignoring first match since its entire string in the capture group always
				//ignoring second match since its the index to generate col and row idx
				const std::int64_t rowIdx{ std::stoi(matches[2].str()) };
				const std::int64_t colIdx{ std::stoi(matches[3].str()) };

				//set the tile type
				gridLayoutComponent->SetTileType(rowIdx, colIdx, matches[4].str());

				//if the tile type was either of these nothing to do
				if (matches[4] == rgx::WALL || matches[4] == rgx::UNREACHABLE)
				{
					continue;
				}

				//if none found nothing to do
				if (matches[5] == rgx::NOTHING_TO_SPAWN)
				{
					continue;
				}

				//if small spawn small pickup 
				if (matches[5] == rgx::PICKUP_SMALL)
				{
					SpawnSmallPickup(scenePtr, rowIdx, colIdx);
				}
				//if big spawn big pickup
				else if (matches[5] == rgx::PICKUP_BIG)
				{
					SpawnBigPickup(scenePtr, rowIdx, colIdx);
				}

				else if (matches[5] == rgx::BLINKY_SPAWN)
				{
					SpawnBlinky(scenePtr, gridLayoutComponent, pacmanPtr, rowIdx, colIdx);
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
		using SoundId = pacman::resources::sound::SoundId;
		using InpMan = amu::InputManager;

		std::unique_ptr backgroundUPtr{ std::make_unique<amu::GameObject>() };
		backgroundUPtr->AddComponent<amu::TransformComponent>(backgroundUPtr.get(), glm::vec2{ pacman::config::WINDOW_WIDTH / 2, pacman::config::WINDOW_HEIGHT / 2 });

		amu::RenderComponent* renderComponentPtr{ backgroundUPtr->AddComponent<amu::RenderComponent>(backgroundUPtr.get(), resources::sprites::PLAYINGFIELD.FilePath) };
		renderComponentPtr->SetSourceRectangle(SDL_Rect{ 0, 0, renderComponentPtr->GetSize().x, renderComponentPtr->GetSize().y });

		std::unique_ptr fpsCounterUPtr{ std::make_unique<amu::GameObject>() };
		fpsCounterUPtr->AddComponent<amu::TransformComponent>(fpsCounterUPtr.get(), glm::vec2{ 50 , 50 });
		fpsCounterUPtr->AddComponent<amu::TextComponent>(fpsCounterUPtr.get(), "60", resources::font::LINGUA, 36);
		fpsCounterUPtr->AddComponent<FPSComponent>(fpsCounterUPtr.get());

		scenePtr->Add(std::move(backgroundUPtr));

		PopulatePlayingGrid(scenePtr);

		scenePtr->Add(std::move(fpsCounterUPtr));
	}

}

#endif