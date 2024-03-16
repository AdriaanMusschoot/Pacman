#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Base/Minigin.h"
#include "Singletons/SceneManager.h"
#include "Singletons/ResourceManager.h"
#include "Singletons/InputManager.h"
#include "Base/GameObject.h"
#include "Commands/MoveCommands.h"
#include "Parameters.h"
#include "Base/Scene.h"
#include <filesystem>

#include "Components/AutoRotateComponent.h"
#include "Components/FPSComponent.h"
#include "Components/TextComponent.h"
#include "Components/TextureComponent.h"
#include "Components/TrashTheCacheEx1Component.h"
#include "Components/TrashTheCacheEx2Component.h"
#include "Components/MoveableComponent.h"
#include "SDL_egl.h"
#include <iostream>
#include "windows.h"
#include "Xinput.h"

namespace fs = std::filesystem;

void load()
{
	auto& scene = amu::SceneManager::GetInstance().CreateScene("Programming 4 Assignment");

	//////////////////////////////////////////
	///////////////BACKGROUND + FPS
	//////////////////////////////////////////

	std::unique_ptr backgroundUPtr{ std::make_unique<amu::GameObject>() };
	backgroundUPtr->AddComponent<amu::TransformComponent>(backgroundUPtr.get(), glm::vec3{0, 0, 0});
	backgroundUPtr->AddComponent<amu::TextureComponent>(backgroundUPtr.get());
	if (backgroundUPtr->ComponentAdded<amu::TextureComponent>())
	{
		backgroundUPtr->GetComponent<amu::TextureComponent>()->SetTexture("background.tga");
	}
	
	std::unique_ptr daeLogoUPtr{ std::make_unique<amu::GameObject>() };
	daeLogoUPtr->AddComponent<amu::TransformComponent>(daeLogoUPtr.get(), glm::vec3{amu::WINDOW_WIDTH / 2 - 103, amu::WINDOW_HEIGHT / 2 - 24, 0 });
	daeLogoUPtr->AddComponent<amu::TextureComponent>(daeLogoUPtr.get());
	if (daeLogoUPtr->ComponentAdded<amu::TextureComponent>())
	{
		daeLogoUPtr->GetComponent<amu::TextureComponent>()->SetTexture("logo.tga");
	}
 	daeLogoUPtr->SetParent(backgroundUPtr.get(), false);

	std::unique_ptr titleUPtr{ std::make_unique<amu::GameObject>() };
	titleUPtr->AddComponent<amu::TransformComponent>(titleUPtr.get(), glm::vec3{ 80, 20, 0 });
	titleUPtr->AddComponent<amu::TextComponent>(titleUPtr.get(), "Programming 4 Assignment", "Lingua.otf", 36);
 	titleUPtr->SetParent(backgroundUPtr.get(), false);
	
	std::unique_ptr fpsCounterUPtr{ std::make_unique<amu::GameObject>() };
	fpsCounterUPtr->AddComponent<amu::TransformComponent>(fpsCounterUPtr.get(), glm::vec3{ 0, 50, 0 });
	fpsCounterUPtr->AddComponent<amu::TextComponent>(fpsCounterUPtr.get(), "60", "Lingua.otf", 36);
	fpsCounterUPtr->AddComponent<amu::FPSComponent>(fpsCounterUPtr.get());
 	fpsCounterUPtr->SetParent(backgroundUPtr.get(), false);

	scene.Add(std::move(backgroundUPtr));
	scene.Add(std::move(daeLogoUPtr));
	scene.Add(std::move(titleUPtr));
	scene.Add(std::move(fpsCounterUPtr));
	//////////////////////////////////////////
	///////////////ROTATING PACMANS
	//////////////////////////////////////////

	std::unique_ptr pacmanUPtr{ std::make_unique<amu::GameObject>() };
	pacmanUPtr->AddComponent<amu::TransformComponent>(pacmanUPtr.get(), glm::vec3{amu::WINDOW_WIDTH / 2 - 4, amu::WINDOW_HEIGHT / 2 - 4, 0 });
	pacmanUPtr->AddComponent<amu::TextureComponent>(pacmanUPtr.get());
	if (pacmanUPtr->ComponentAdded<amu::TextureComponent>())
	{
		pacmanUPtr->GetComponent<amu::TextureComponent>()->SetTexture("PacMan.png");
	}
	pacmanUPtr->AddComponent<amu::MoveableComponent>(pacmanUPtr.get(), 20);

	std::unique_ptr blueGhostUPtr{ std::make_unique<amu::GameObject>() };
	blueGhostUPtr->AddComponent<amu::TransformComponent>(blueGhostUPtr.get(), glm::vec3{amu::WINDOW_WIDTH / 2 - 4, amu::WINDOW_HEIGHT / 2 - 4, 0 });
	blueGhostUPtr->AddComponent<amu::TextureComponent>(blueGhostUPtr.get());
	if (blueGhostUPtr->ComponentAdded<amu::TextureComponent>())
	{
		blueGhostUPtr->GetComponent<amu::TextureComponent>()->SetTexture("BlueGhost.png");
	}
	blueGhostUPtr->AddComponent<amu::MoveableComponent>(blueGhostUPtr.get(), 40);

	/////////////////////////////
	/////////Add commmands
	/////////////////////////////
	amu::InputManager::GetInstance().AddCommandController(
		XINPUT_GAMEPAD_DPAD_RIGHT,
		amu::InputManager::InputState::Held,
		std::make_unique<amu::MoveRight>(pacmanUPtr.get()));

	amu::InputManager::GetInstance().AddCommandController(
		XINPUT_GAMEPAD_DPAD_LEFT,
		amu::InputManager::InputState::Held,
		std::make_unique<amu::MoveLeft>(pacmanUPtr.get()));

	amu::InputManager::GetInstance().AddCommandController(
		XINPUT_GAMEPAD_DPAD_UP,
		amu::InputManager::InputState::Held,
		std::make_unique<amu::MoveUp>(pacmanUPtr.get()));

	amu::InputManager::GetInstance().AddCommandController(
		XINPUT_GAMEPAD_DPAD_DOWN,
		amu::InputManager::InputState::Held,
		std::make_unique<amu::MoveDown>(pacmanUPtr.get()));

	amu::InputManager::GetInstance().AddCommandKeyboard(
		SDLK_d,
		amu::InputManager::InputState::Held,
		std::make_unique<amu::MoveRight>(blueGhostUPtr.get()));

	amu::InputManager::GetInstance().AddCommandKeyboard(
		SDLK_a,
		amu::InputManager::InputState::Held,
		std::make_unique<amu::MoveLeft>(blueGhostUPtr.get()));

	amu::InputManager::GetInstance().AddCommandKeyboard(
		SDLK_w,
		amu::InputManager::InputState::Held,
		std::make_unique<amu::MoveUp>(blueGhostUPtr.get()));

	amu::InputManager::GetInstance().AddCommandKeyboard(
		SDLK_s,
		amu::InputManager::InputState::Held,
		std::make_unique<amu::MoveDown>(blueGhostUPtr.get()));

	scene.Add(std::move(pacmanUPtr));
	scene.Add(std::move(blueGhostUPtr));
}

int main(int, char*[]) {
#ifdef WIN32
	if (AllocConsole()) {
		FILE* pEmpty;
		freopen_s(&pEmpty, "CONOUT$", "w", stdout);
		freopen_s(&pEmpty, "CONOUT$", "w", stderr);
}
#endif

#if __EMSCRIPTEN__
	fs::path data_location = "";
#else
	fs::path data_location = "./Data/";
	if(!fs::exists(data_location))
		data_location = "../Data/";
#endif
	amu::Minigin engine(data_location);
	engine.Run(load);
    return 0;
}
