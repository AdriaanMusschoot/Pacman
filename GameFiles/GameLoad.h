#ifndef PACMAN_GAMELOAD_H
#define PACMAN_GAMELOAD_H

#include <Scene.h>
#include <SceneManager.h>

#include <Component.h>
#include <GameObject.h>

#include <TextureComponent.h>
#include <TransformComponent.h>

namespace PacMan
{

	void LoadGame(amu::Scene* scenePtr)
	{
		std::unique_ptr titleUPtr{ std::make_unique<amu::GameObject>() };
	
		titleUPtr->AddComponent<amu::TransformComponent>(titleUPtr.get(), glm::vec2{ 0, 0 });
		titleUPtr->AddComponent<amu::RenderComponent>(titleUPtr.get(), "background.tga");
	
		scenePtr->Add(std::move(titleUPtr));
	}

}

#endif