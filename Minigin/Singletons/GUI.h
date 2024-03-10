#pragma once
#include "Singleton.h"

struct SDL_Window;
struct SDL_Renderer;
union SDL_Event;

namespace amu
{

	class GUI final: public Singleton<GUI>
	{
	public:
		void Initialize(SDL_Window* windowPtr, SDL_Renderer* randererPtr);
	
		void BeginFrame() const;
		void EndFrame() const;
		void Destroy();
	
		bool ProcessEvent(SDL_Event* eventPtr);
	};

}