#include "Controller.h"

namespace amu
{

	class Controller::ControllerImpl
	{
	public:
		void AddCommand(unsigned int button, amu::InputManager::InputState state, std::unique_ptr<amu::GameObjectCommand> commandPtr)
		{
			m_ControllerCommandPtrVec.emplace_back(std::make_tuple(button, state, std::move(commandPtr)));
		}
	
		void ProcessControllerInput(int controllerIndex)
		{
			CopyMemory(&m_PreviousStateController, &m_CurrentStateController, sizeof(XINPUT_STATE));
			ZeroMemory(&m_CurrentStateController, sizeof(XINPUT_STATE));
			XInputGetState(controllerIndex, &m_CurrentStateController);
	
			const auto buttonChangesController = m_CurrentStateController.Gamepad.wButtons ^ m_PreviousStateController.Gamepad.wButtons;
			const auto buttonsPressedThisFrameController = buttonChangesController & m_CurrentStateController.Gamepad.wButtons;
			const auto buttonsReleasedThisFrameController = buttonChangesController & (~m_CurrentStateController.Gamepad.wButtons);
	
			for (const auto& [button, state, command] : m_ControllerCommandPtrVec)
			{
				switch (state)
				{
				case amu::InputManager::InputState::Pressed:
					if (buttonsPressedThisFrameController & button)
					{
						command->Execute();
					}
					break;
				case amu::InputManager::InputState::Released:
					if (buttonsReleasedThisFrameController & button)
					{
						command->Execute();
					}
					break;
				case amu::InputManager::InputState::Held:
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
	
		std::vector<std::tuple<unsigned int, amu::InputManager::InputState, std::unique_ptr<amu::GameObjectCommand>>> m_ControllerCommandPtrVec;
	};

}

amu::Controller::Controller(int controllerIndex)
	: m_ControllerImplPtr{ std::make_unique<ControllerImpl>() }
	, m_ControllerIndex{ controllerIndex }
{
}

amu::Controller::~Controller()
{

}

void amu::Controller::AddCommand(unsigned int button, InputManager::InputState state, std::unique_ptr<GameObjectCommand> commandPtr)
{
	m_ControllerImplPtr->AddCommand(button, state, std::move(commandPtr));
}

void amu::Controller::ProcessControllerInput()
{
	m_ControllerImplPtr->ProcessControllerInput(m_ControllerIndex);
}
