#pragma once
#include "Singleton.h"
#include "windows.h"
#include "XInput.h"
#include "Commands/GameActorCommands.h"

namespace amu
{

	class InputManager final : public Singleton<InputManager>
	{
	public:
		enum class InputState
		{
			Pressed,
			Released,
			Held
		};

		void AddCommandController(unsigned int button, InputState state, std::unique_ptr<GameActorCommand> commandPtr);

		void AddCommandKeyboard(unsigned int button, InputState state, std::unique_ptr<GameActorCommand> commandPtr);

		bool ProcessInput();
	private:
		XINPUT_STATE m_PreviousStateController;
		XINPUT_STATE m_CurrentStateController;

		std::vector<std::tuple<unsigned int, InputState, std::unique_ptr<GameActorCommand>>> m_ControllerCommandPtrVec;

		Uint32 m_PreviousStateKeyboard;
		Uint32 m_CurrentStateKeyboard;

		std::vector<std::tuple<unsigned int, InputState, std::unique_ptr<GameActorCommand>>> m_KeyboardCommandPtrVec;
	};

}
