#include <SDL.h>
#include "Singletons/InputManager.h"
#include "Singletons/GUI.h"
#include <iostream>

void amu::InputManager::AddCommandController(unsigned int button, InputState state, std::unique_ptr<GameActorCommand> commandPtr)
{
	m_ControllerCommandPtrVec.emplace_back(std::make_tuple(button, state, std::move(commandPtr)));
}

void amu::InputManager::AddCommandKeyboard(unsigned int button, InputState state, std::unique_ptr<GameActorCommand> commandPtr)
{
	m_KeyboardCommandPtrVec.emplace_back(std::make_tuple(button, state, std::move(commandPtr)));
}

bool amu::InputManager::ProcessInput()
{
	////////////////////////////////////////
	///////////Xbox Input handling
	////////////////////////////////////////
	CopyMemory(&m_PreviousStateController, &m_CurrentStateController, sizeof(XINPUT_STATE));
	ZeroMemory(&m_CurrentStateController, sizeof(XINPUT_STATE));
	XInputGetState(0, &m_CurrentStateController);

	auto buttonChangesController = m_CurrentStateController.Gamepad.wButtons ^ m_PreviousStateController.Gamepad.wButtons;
	auto buttonsPressedThisFrameController = buttonChangesController & m_CurrentStateController.Gamepad.wButtons;
	auto buttonsReleasedThisFrameController = buttonChangesController & (~m_CurrentStateController.Gamepad.wButtons);
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

	////////////////////////////////////////
	///////////IMGUI Input handling
	////////////////////////////////////////
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (GUI::GetInstance().ProcessEvent(&e))
		{
			continue;
		}
		if (e.type == SDL_QUIT)
		{
			return false;
		}
	}
	////////////////////////////////////////
	///////////Keyboard Input handling
	////////////////////////////////////////
	m_PreviousStateKeyboard = m_CurrentStateKeyboard;

	const Uint8* currentKeyState = SDL_GetKeyboardState(nullptr);

	for (int i = 0; i < SDL_NUM_SCANCODES; ++i) 
	{
		if (currentKeyState[i]) 
		{
			m_CurrentStateKeyboard |= (1 << i);
		}
	}

	auto buttonChangesKeyboard = m_CurrentStateKeyboard ^ m_PreviousStateKeyboard;
	auto buttonsPressedThisFrameKeyboard = buttonChangesKeyboard & m_CurrentStateKeyboard;
	auto buttonsReleasedThisFrameKeyboard = buttonChangesKeyboard & (~m_CurrentStateKeyboard);

	for (const auto& [button, state, command] : m_KeyboardCommandPtrVec)
	{
		switch (state)
		{
		case InputState::Pressed:
			if (buttonsPressedThisFrameKeyboard & button)
			{
				command->Execute();
			}
			break;
		case InputState::Released:
			if (buttonsReleasedThisFrameKeyboard & button)
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

	return true;
}