#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "Header\SceneManager.h"
#include "Header\ResourceManager.h"
#include "Header\GameObject.h"
#include "Header\Scene.h"
#include <filesystem>

#include "Header/AutoRotateComponent.h"
#include "Header/FPSComponent.h"
#include "Header/TextComponent.h"
#include "Header/TextureComponent.h"
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

	std::unique_ptr backgroundSPtr{ std::make_unique<amu::GameObject>() };
	backgroundSPtr->AddComponent<amu::TransformComponent>(backgroundSPtr.get(), glm::vec3{0, 0, 0});
	backgroundSPtr->AddComponent<amu::TextureComponent>(backgroundSPtr.get());
	if (backgroundSPtr->ComponentAdded<amu::TextureComponent>())
	{
		backgroundSPtr->GetComponent<amu::TextureComponent>()->SetTexture("background.tga");
	}
	
	std::unique_ptr daeLogoSPtr{ std::make_unique<amu::GameObject>() };
	daeLogoSPtr->AddComponent<amu::TransformComponent>(daeLogoSPtr.get(), glm::vec3{amu::WINDOW_WIDTH / 2 - 103, amu::WINDOW_HEIGHT / 2 - 24, 0 });
	daeLogoSPtr->AddComponent<amu::TextureComponent>(daeLogoSPtr.get());
	if (daeLogoSPtr->ComponentAdded<amu::TextureComponent>())
	{
		daeLogoSPtr->GetComponent<amu::TextureComponent>()->SetTexture("logo.tga");
	}
 	daeLogoSPtr->SetParent(backgroundSPtr.get(), false);

	std::unique_ptr titleSPtr{ std::make_unique<amu::GameObject>() };
	titleSPtr->AddComponent<amu::TransformComponent>(titleSPtr.get(), glm::vec3{ 80, 20, 0 });
	titleSPtr->AddComponent<amu::TextComponent>(titleSPtr.get(), "Programming 4 Assignment", "Lingua.otf", 36);
 	titleSPtr->SetParent(backgroundSPtr.get(), false);
	
	std::unique_ptr fpsCounterSPtr{ std::make_unique<amu::GameObject>() };
	fpsCounterSPtr->AddComponent<amu::TransformComponent>(fpsCounterSPtr.get(), glm::vec3{ 0, 50, 0 });
	fpsCounterSPtr->AddComponent<amu::TextComponent>(fpsCounterSPtr.get(), "60", "Lingua.otf", 36);
	fpsCounterSPtr->AddComponent<amu::FPSComponent>(fpsCounterSPtr.get());
 	fpsCounterSPtr->SetParent(backgroundSPtr.get(), false);

	scene.Add(std::move(backgroundSPtr));
	scene.Add(std::move(daeLogoSPtr));
	scene.Add(std::move(titleSPtr));
	scene.Add(std::move(fpsCounterSPtr));
	//////////////////////////////////////////
	///////////////ROTATING PACMANS
	//////////////////////////////////////////

	std::unique_ptr pacman1SPtr{ std::make_unique<amu::GameObject>() };
	pacman1SPtr->AddComponent<amu::TransformComponent>(pacman1SPtr.get(), glm::vec3{amu::WINDOW_WIDTH / 2 - 4, amu::WINDOW_HEIGHT / 2 - 4, 0 });
	pacman1SPtr->AddComponent<amu::TextureComponent>(pacman1SPtr.get());
	if (pacman1SPtr->ComponentAdded<amu::TextureComponent>())
	{
		pacman1SPtr->GetComponent<amu::TextureComponent>()->SetTexture("PacMan.png");
	}
	pacman1SPtr->AddComponent<amu::AutoRotateComponent>(pacman1SPtr.get(), 20, 3.0);

	constexpr int nrPerCircle{ 20 };
	constexpr double incAngle{ 360.0 * amu::TO_RADIANS / nrPerCircle };

	for (int idx{}; idx < nrPerCircle; ++idx)
	{
		std::unique_ptr pacman2SPtr{ std::make_unique<amu::GameObject>() };
		pacman2SPtr->AddComponent<amu::TransformComponent>(pacman2SPtr.get(), glm::vec3{ 0, 0, 0 });
		pacman2SPtr->SetParent(pacman1SPtr.get(), false);
		pacman2SPtr->AddComponent<amu::TextureComponent>(pacman2SPtr.get());
		if (pacman2SPtr->ComponentAdded<amu::TextureComponent>())
		{
			pacman2SPtr->GetComponent<amu::TextureComponent>()->SetTexture("PacMan.png");
		}
		pacman2SPtr->AddComponent<amu::AutoRotateComponent>(pacman2SPtr.get(), 100, 0.1 * idx, idx * incAngle);

		constexpr int nrPerCircle2{ nrPerCircle };
		constexpr double incAngle2{ 360.0 * amu::TO_RADIANS / nrPerCircle2 };

		for (int idx1{}; idx1 < nrPerCircle2; ++idx1)
		{
		std::unique_ptr pacman3SPtr{ std::make_unique<amu::GameObject>() };
			pacman3SPtr->AddComponent<amu::TransformComponent>(pacman3SPtr.get(), glm::vec3{ 0, 0, 0 });
			pacman3SPtr->SetParent(pacman2SPtr.get(), false);
			pacman3SPtr->AddComponent<amu::TextureComponent>(pacman3SPtr.get());
			if (pacman3SPtr->ComponentAdded<amu::TextureComponent>())
			{
				pacman3SPtr->GetComponent<amu::TextureComponent>()->SetTexture("PacMan.png");
			}
			pacman3SPtr->AddComponent<amu::AutoRotateComponent>(pacman3SPtr.get(), 50, 0.1 * idx1, idx1 * incAngle2);
			//pacman3SPtr->SetParent(nullptr, true);
			scene.Add(std::move(pacman3SPtr));
			std::cout << idx1 + idx * nrPerCircle2 << "\n";
		}
		scene.Add(std::move(pacman2SPtr));
	}
	scene.Add(std::move(pacman1SPtr));
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
