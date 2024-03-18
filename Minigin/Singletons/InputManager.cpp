#include <SDL.h>
#include "Singletons/InputManager.h"
#include "Singletons/GUI.h"
#include <iostream>
#include "windows.h"
#include "XInput.h"

class amu::InputManager::ControllerInputImpl
{
public:
	void AddCommand(unsigned int button, InputState state, std::unique_ptr<GameObjectCommand> commandPtr)
	{
		m_ControllerCommandPtrVec.emplace_back(std::make_tuple(button, state, std::move(commandPtr)));
	}

	void ProcessControllerInput()
	{
		CopyMemory(&m_PreviousStateController, &m_CurrentStateController, sizeof(XINPUT_STATE));
		ZeroMemory(&m_CurrentStateController, sizeof(XINPUT_STATE));
		XInputGetState(0, &m_CurrentStateController);

		const auto buttonChangesController = m_CurrentStateController.Gamepad.wButtons ^ m_PreviousStateController.Gamepad.wButtons;
		const auto buttonsPressedThisFrameController = buttonChangesController & m_CurrentStateController.Gamepad.wButtons;
		const auto buttonsReleasedThisFrameController = buttonChangesController & (~m_CurrentStateController.Gamepad.wButtons);
		for (const auto& [button, state, command] : m_ControllerCommandPtrVec)
		{
			switch (state)
			{
			case InputState::Pressed:
				if (buttonsPressedThisFrameController & button)
				{
					command->Execute();
				}
				break;
			case InputState::Released:
				if (buttonsReleasedThisFrameController & button)
				{
					command->Execute();
				}
				break;
			case InputState::Held:
				if (m_CurrentStateController.Gamepad.wButtons & button)
				{
					command->Execute();
				}
				break;
			}
		}
	}
private:
	XINPUT_STATE m_PreviousStateController;
	XINPUT_STATE m_CurrentStateController;

	std::vector<std::tuple<unsigned int, InputState, std::unique_ptr<GameObjectCommand>>> m_ControllerCommandPtrVec;
};

amu::InputManager::InputManager()
	: m_ControllerInputImplPtr{ new ControllerInputImpl() }
{
}

void amu::InputManager::AddCommandController(unsigned int button, InputState state, std::unique_ptr<GameObjectCommand> commandPtr)
{
	m_ControllerInputImplPtr->AddCommand(button, state, std::move(commandPtr));
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