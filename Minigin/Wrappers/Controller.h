#pragma once
#include "Windows.h"
#include "Xinput.h"
#include <vector>
#include <tuple>
#include "Singletons/InputManager.h"
#include "Commands/GameObjectCommands.h"

namespace amu
{

	class Controller final
	{
	public:
		Controller(int controllerIndex);
		~Controller();

		void AddCommand(unsigned int button, InputManager::InputState state, std::unique_ptr<GameObjectCommand> commandPtr);
		void ProcessControllerInput();

	private:
		class ControllerImpl;
		std::unique_ptr<ControllerImpl> m_ControllerImplPtr;

		int m_ControllerIndex;
	};

}