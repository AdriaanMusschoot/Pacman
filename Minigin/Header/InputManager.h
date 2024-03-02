#pragma once
#include "Singleton.h"

namespace amu
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
	};

}
