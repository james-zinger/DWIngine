#include "Input.h"

namespace DWI
{

	Input::Input(void)
	{
		ParamList pl;
		size_t windowHnd;
		//std::ostringstream windowHndStr;
		

		__inputManager = InputManager::createInputSystem(pl);
	}


	Input::~Input(void)
	{

	}
}