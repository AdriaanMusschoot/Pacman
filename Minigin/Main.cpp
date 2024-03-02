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

namespace fs = std::filesystem;

void load()
{
	auto& scene = amu::SceneManager::GetInstance().CreateScene("Programming 4 Assignment");

	std::shared_ptr backgroundSPtr{ std::make_shared<amu::GameObject>() };
	backgroundSPtr->AddComponent<amu::TransformComponent>(backgroundSPtr, glm::vec3{ 0, 0, 0 });
	backgroundSPtr->AddComponent<amu::TextureComponent>(backgroundSPtr);
	if (backgroundSPtr->ComponentAdded<amu::TextureComponent>())
	{
		backgroundSPtr->GetComponent<amu::TextureComponent>()->SetTexture("background.tga");
	}
	scene.Add(backgroundSPtr);
	
	std::shared_ptr daeLogoSPtr{ std::make_shared<amu::GameObject>() };
	daeLogoSPtr->AddComponent<amu::TransformComponent>(daeLogoSPtr, glm::vec3{ WINDOW_WIDTH / 2 - 103, WINDOW_HEIGHT / 2 - 24, 0 });
	daeLogoSPtr->AddComponent<amu::TextureComponent>(daeLogoSPtr);
	if (daeLogoSPtr->ComponentAdded<amu::TextureComponent>())
	{
		daeLogoSPtr->GetComponent<amu::TextureComponent>()->SetTexture("logo.tga");
	}
 	daeLogoSPtr->SetParent(backgroundSPtr.get(), false);
	scene.Add(daeLogoSPtr);

	std::shared_ptr titleSPtr{ std::make_shared<amu::GameObject>() };
	titleSPtr->AddComponent<amu::TransformComponent>(titleSPtr, glm::vec3{ 80, 20, 0 });
	titleSPtr->AddComponent<amu::TextComponent>(titleSPtr, "Programming 4 Assignment", "Lingua.otf", 36);
 	titleSPtr->SetParent(backgroundSPtr.get(), false);
	scene.Add(titleSPtr);
	
	std::shared_ptr fpsCounterSPtr{ std::make_shared<amu::GameObject>() };
	fpsCounterSPtr->AddComponent<amu::TransformComponent>(fpsCounterSPtr, glm::vec3{ 0, 50, 0 });
	fpsCounterSPtr->AddComponent<amu::TextComponent>(fpsCounterSPtr, "60", "Lingua.otf", 36);
	fpsCounterSPtr->AddComponent<amu::FPSComponent>(fpsCounterSPtr);
 	fpsCounterSPtr->SetParent(backgroundSPtr.get(), false);
	scene.Add(fpsCounterSPtr);

	std::shared_ptr pacman1SPtr{ std::make_shared<amu::GameObject>() };
	pacman1SPtr->AddComponent<amu::TransformComponent>(pacman1SPtr, glm::vec3{ WINDOW_WIDTH / 2 - 16, WINDOW_HEIGHT / 2 - 16, 0 });
	pacman1SPtr->AddComponent<amu::TextureComponent>(pacman1SPtr);
	if (pacman1SPtr->ComponentAdded<amu::TextureComponent>())
	{
		pacman1SPtr->GetComponent<amu::TextureComponent>()->SetTexture("PacMan.png");
	}
	pacman1SPtr->AddComponent<amu::AutoRotateComponent>(pacman1SPtr, 100, 3.0);
	scene.Add(pacman1SPtr);

	std::shared_ptr pacman2SPtr{ std::make_shared<amu::GameObject>() };
	pacman2SPtr->AddComponent<amu::TransformComponent>(pacman2SPtr, glm::vec3{ 0, 0, 0 });
	pacman2SPtr->SetParent(pacman1SPtr.get(), false);
	pacman2SPtr->AddComponent<amu::TextureComponent>(pacman2SPtr);
	if (pacman2SPtr->ComponentAdded<amu::TextureComponent>())
	{
		pacman2SPtr->GetComponent<amu::TextureComponent>()->SetTexture("PacMan.png");
	}
	pacman2SPtr->AddComponent<amu::AutoRotateComponent>(pacman2SPtr, 50, 5.0);
	scene.Add(pacman2SPtr);
}

int main(int, char*[]) {
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
