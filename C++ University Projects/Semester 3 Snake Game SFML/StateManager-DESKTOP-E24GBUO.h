#pragma once
#include <stack>
#include <memory>
#include "State.h"

namespace Engine
{
	class StateManager
	{
		std::stack<std::unique_ptr<State>> StateStack_ptr; //Stack for unique pointers(pointers to objects i.e states)
		std::unique_ptr<State> NewState_ptr; //New state pointer

		bool s_add;
		bool s_replace;
		bool s_remove;

	public:
		StateManager();
		~StateManager();

		void PutOnStack(std::unique_ptr<State> add, bool replace = false); //Adding to stack and checking if state can be added on top or should be replaced
		void PopOutStack(); //Removing state from the stack
		void StateChange(); //All stack modification are performed here
		std::unique_ptr<State>& GetCurrent(); //Getting current pointer
	};
}