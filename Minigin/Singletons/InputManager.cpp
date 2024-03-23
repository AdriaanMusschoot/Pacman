#include <SDL.h>
#include "Singletons/InputManager.h"
#include "Singletons/GUI.h"
#include "Wrappers/Controller.h"
#include <array>

class amu::InputManager::ControllerInputImpl
{
public:
	void AddCommand(unsigned int controllerIdx, unsigned int button, InputState state, std::unique_ptr<GameObjectCommand> commandPtr)
	{
		for (size_t idx{}; idx < m_ControllerArr.size(); ++idx)
		{
			if (idx == controllerIdx)
			{
				m_ControllerArr[idx].AddCommand(button, state, std::move(commandPtr));
			}
		}
	}

	void ProcessControllerInput()
	{
		for (Controller& controller : m_ControllerArr)
		{
			controller.ProcessControllerInput();
		}
	}
private:
	std::array<Controller, 2> m_ControllerArr{ Controller{ 0 }, Controller{ 1 } };
};

amu::InputManager::InputManager()
	: m_ControllerInputImplPtr{ std::make_unique<ControllerInputImpl>() }
{

}

amu::InputManager::~InputManager()
{
	/////EMPTY DESTRUCTOR TO DELETE UNIQUE PTR OTHERWISE CRASH DONT TOUCH
}

void amu::InputManager::AddCommandController(unsigned int controllerIdx, unsigned int button, InputState state, std::unique_ptr<GameObjectCommand> commandPtr)
{
	m_ControllerInputImplPtr->AddCommand(controllerIdx, button, state, std::move(commandPtr));
}

void amu::InputManager::AddCommandKeyboard(unsigned int button, InputState state, std::unique_ptr<GameObjectCommand> commandPtr)
{
	m_KeyboardCommandPtrVec.emplace_back(std::make_tuple(button, state, std::move(commandPtr)));
}

bool amu::InputManager::ProcessInput()
{
	////////////////////////////////////////
	///////////Xbox Input handling
	////////////////////////////////////////
	m_ControllerInputImplPtr->ProcessControllerInput();
	

	////////////////////////////////////////
	///////////Keyboard and Mouse Input handling
	////////////////////////////////////////
	m_PreviousStateKeyboard = m_CurrentStateKeyboard;

	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
		{
			return false;
		}
		if (e.type == SDL_KEYDOWN)
		{
			m_CurrentStateKeyboard[e.key.keysym.sym] = true;
		}
		if (e.type == SDL_KEYUP)
		{
			m_CurrentStateKeyboard[e.key.keysym.sym] = false;
		}
		if (GUI::GetInstance().ProcessEvent(&e))
		{
			continue;
		}
	}
	
	for (const auto& [button, state, command] : m_KeyboardCommandPtrVec)
	{
		const bool buttonChangedThisFrame{ m_CurrentStateKeyboard[button] != m_PreviousStateKeyboard[button] };
		const bool buttonPressedThisFrame{ buttonChangedThisFrame && m_CurrentStateKeyboard[button] };
		const bool buttonReleasedThisFrame{ buttonChangedThisFrame && !m_CurrentStateKeyboard[button] };
		switch (state)
		{
		case InputState::Pressed:
			if (buttonPressedThisFrame && buttonChangedThisFrame)
			{
				command->Execute();
			}
			break;
		case InputState::Released:
			if (buttonReleasedThisFrame && buttonChangedThisFrame)
			{
				command->Execute();
			}
			break;
		case InputState::Held:
			if (m_CurrentStateKeyboard[button])
			{
				command->Execute();
			}
			break;
		}
	}

	return true;
}