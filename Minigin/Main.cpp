#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Base/Minigin.h"
#include "Singletons\SceneManager.h"
#include "Singletons\ResourceManager.h"
#include "Base\GameObject.h"
#include "Base\Scene.h"
#include <filesystem>

#include "Components/AutoRotateComponent.h"
#include "Components/FPSComponent.h"
#include "Components/TextComponent.h"
#include "Components/TextureComponent.h"
#include "Components/TrashTheCacheComponent.h"
#include "Parameters.h"
#include "SDL_egl.h"
#include <iostream>

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

	std::unique_ptr pacman1UPtr{ std::make_unique<amu::GameObject>() };
	pacman1UPtr->AddComponent<amu::TransformComponent>(pacman1UPtr.get(), glm::vec3{amu::WINDOW_WIDTH / 2 - 4, amu::WINDOW_HEIGHT / 2 - 4, 0 });
	pacman1UPtr->AddComponent<amu::TextureComponent>(pacman1UPtr.get());
	if (pacman1UPtr->ComponentAdded<amu::TextureComponent>())
	{
		pacman1UPtr->GetComponent<amu::TextureComponent>()->SetTexture("PacMan.png");
	}
	pacman1UPtr->AddComponent<amu::AutoRotateComponent>(pacman1UPtr.get(), 20, 3.0);

	constexpr int nrPerCircle{ 20 };
	constexpr double incAngle{ 360.0 * amu::TO_RADIANS / nrPerCircle };

	for (int idx{}; idx < nrPerCircle; ++idx)
	{
		std::unique_ptr pacman2UPtr{ std::make_unique<amu::GameObject>() };
		pacman2UPtr->AddComponent<amu::TransformComponent>(pacman2UPtr.get(), glm::vec3{ 0, 0, 0 });
		pacman2UPtr->SetParent(pacman1UPtr.get(), false);
		pacman2UPtr->AddComponent<amu::TextureComponent>(pacman2UPtr.get());
		if (pacman2UPtr->ComponentAdded<amu::TextureComponent>())
		{
			pacman2UPtr->GetComponent<amu::TextureComponent>()->SetTexture("PacMan.png");
		}
		pacman2UPtr->AddComponent<amu::AutoRotateComponent>(pacman2UPtr.get(), 100, 0.1 * idx, idx * incAngle);

		constexpr int nrPerCircle2{ nrPerCircle };
		constexpr double incAngle2{ 360.0 * amu::TO_RADIANS / nrPerCircle2 };

		for (int idx1{}; idx1 < nrPerCircle2; ++idx1)
		{
		std::unique_ptr pacman3UPtr{ std::make_unique<amu::GameObject>() };
			pacman3UPtr->AddComponent<amu::TransformComponent>(pacman3UPtr.get(), glm::vec3{ 0, 0, 0 });
			pacman3UPtr->SetParent(pacman2UPtr.get(), false);
			pacman3UPtr->AddComponent<amu::TextureComponent>(pacman3UPtr.get());
			if (pacman3UPtr->ComponentAdded<amu::TextureComponent>())
			{
				pacman3UPtr->GetComponent<amu::TextureComponent>()->SetTexture("PacMan.png");
			}
			pacman3UPtr->AddComponent<amu::AutoRotateComponent>(pacman3UPtr.get(), 50, 0.1 * idx1, idx1 * incAngle2);
			//pacman3SPtr->SetParent(nullptr, true);
			scene.Add(std::move(pacman3UPtr));
		}
		scene.Add(std::move(pacman2UPtr));
	}
	scene.Add(std::move(pacman1UPtr));

	std::unique_ptr TTCObjectEx1UPtr{ std::make_unique<amu::GameObject>() };
	TTCObjectEx1UPtr->AddComponent<amu::TrashTheCacheEx1>(TTCObjectEx1UPtr.get());
	scene.Add(std::move(TTCObjectEx1UPtr));
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
