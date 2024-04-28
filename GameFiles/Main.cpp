#include "Amugen.h"
#include <filesystem>
#include "Windows.h"
#include <iostream>

#include "SceneManager.h"
#include "LoadFunctions.h"
#include "Configuration.h"
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

	amu::Amugen engine(data_location, pacman::config::WIDTH, pacman::config::HEIGHT);

	amu::SceneManager::GetInstance().CreateScene("Pac Man", pacman::LoadGame);

	engine.Run();

    return 0;
}
