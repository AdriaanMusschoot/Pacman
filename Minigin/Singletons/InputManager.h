#pragma once
#include "Singleton.h"
#include "Commands/GameActorCommands.h"
#include <map>
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
		InputManager();
		~InputManager();
		void AddCommandController(unsigned int button, InputState state, std::unique_ptr<GameActorCommand> commandPtr);

		void AddCommandKeyboard(unsigned int button, InputState state, std::unique_ptr<GameActorCommand> commandPtr);

		bool ProcessInput();
	private:
		class ControllerInputImpl;
		ControllerInputImpl* m_ControllerInputImplPtr;

		std::vector<std::tuple<unsigned int, InputState, std::unique_ptr<GameActorCommand>>> m_KeyboardCommandPtrVec;

		std::map<int, bool> m_PreviousStateKeyboard;
		std::map<int, bool> m_CurrentStateKeyboard;

	};

}
