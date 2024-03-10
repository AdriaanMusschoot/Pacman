#include <SDL.h>
#include "Singletons/InputManager.h"
#include "Singletons/GUI.h"
bool amu::InputManager::ProcessInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) 
	{
		if (GUI::GetInstance().ProcessEvent(&e))
			continue;

		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {
			
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			
		}
		// etc...
	}

	return true;
}
