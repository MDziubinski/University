#include "StateManager.h"

Engine::StateManager::StateManager() : s_add(false), s_replace(false), s_remove(false)
{
}

Engine::StateManager::~StateManager()
{
	NewState_ptr = nullptr;
}

void Engine::StateManager::PutOnStack(std::unique_ptr<State> add, bool replace)
{
	s_add = true;
	NewState_ptr = std::move(add);

	s_replace = replace;
}

void Engine::StateManager::PopOutStack()
{
	s_remove = true;
}

void Engine::StateManager::StateChange()
{
	if (s_remove && (!StateStack_ptr.empty()))
	{
		StateStack_ptr.pop();

		if (!StateStack_ptr.empty())
		{
			StateStack_ptr.top()->Start();
		}
		s_remove = false;
	}

	if (s_add)
	{
		if (s_replace && (!StateStack_ptr.empty()))
		{
			StateStack_ptr.pop();
			s_replace = false;
		}

		if (!StateStack_ptr.empty())
		{
			StateStack_ptr.top()->Pause();
		}

		StateStack_ptr.push(std::move(NewState_ptr));
		StateStack_ptr.top()->Initialize();
		StateStack_ptr.top()->Start();
		s_add = false;
	}
}


std::unique_ptr<Engine::State>& Engine::StateManager::GetCurrent()
{
	return StateStack_ptr.top();
}
