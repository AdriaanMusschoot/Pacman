#include "Amugen.h"
#include <filesystem>
#include "Windows.h"
#include <iostream>

#include "SceneManager.h"
#include "ServiceLocator.h"
#include "LoadFunctions.h"
#include "SoundSystem.h"
namespace fs = std::filesystem;

int main(int, char*[]) 
{
	//thx mat for the console fix
#ifdef WIN32
	if (AllocConsole()) 
	{
		FILE* pEmpty;
		freopen_s(&pEmpty, "CONOUT$", "w", stdout);
		freopen_s(&pEmpty, "CONOUT$", "w", stderr);
	}
#endif

	fs::path data_location = "./Resources/";
	if(!fs::exists(data_location))
		data_location = "../Resources/";

	amu::Amugen engine(data_location, 224 * 3, 288 * 3);

	std::unique_ptr sdlSoundSystemUPtr{ std::make_unique<amu::SDLSoundSystem>() };

	amu::ServiceLocator::GetInstance().RegisterSoundSystem(std::move(sdlSoundSystemUPtr));

	amu::SceneManager::GetInstance().CreateScene("Pac Man", pacman::LoadGame);

	engine.Run();

    return 0;
}
