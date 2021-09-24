#pragma once
#include <iostream>


namespace Engine
{
	class State
	{
	public:
		State() {};
		virtual ~State() {}; //As there will be inheritance from this class, it's good manner to set desctructor as virtual to asure memory deallocation

		virtual void Initialize() = 0; //All initializations of state will be triggered here
		virtual void Input_Processing() = 0; //All input will be handled here(Keyboard and mouse)
		virtual void Update() = 0; //Handling FPS (to be revised)
		virtual void Draw() = 0; //Drawing states on the screen

		virtual void Pause() {}; //Pause state (overlaping other states f.ex. playing state)
		virtual void Start() {}; //Start state 
	};
}