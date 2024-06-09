#include "StartGameCommand.h"
#include "SceneManager.h"

void pacman::StartGameCommand::Execute()
{
	amu::SceneManager::GetInstance().SetCurrentScene(tags::MAIN_SCENE);
}
