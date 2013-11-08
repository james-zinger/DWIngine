#include "Input.h"
/////////////////////////////////////////////////////////////////
// Singleton variable

namespace DWI
{
	Input* Input::__singleton = NULL;

	Input::Input(void)
	{
		for (int i = 0; i < GLFWKeys::__COUNT; i++)
		{
			__keyState[i] = false;
			__prevKeyState[i] = false;
		}
	}


	Input::~Input(void)
	{

	}

	Input* DWI::Input::singleton( void )
	{
		if ( __singleton == NULL )
		{
			__singleton = new Input();
		}

		return __singleton;
	}

	void Input::destroySingleton( void )
	{
		if ( __singleton != NULL )
		{
			delete __singleton;
			__singleton = NULL;
		}
}


	void Input::Update( void )
	{
		for(map<int, bool>::iterator it = __keyState.begin(); it != __keyState.end(); it++)
		{
			__prevKeyState[it->first] = it->second;
		}
	}

	bool Input::isKeyDown(GLFWKeys key)
	{
		bool prev = Input::singleton()->__prevKeyState[key];
		bool now = Input::singleton()->__keyState[key];

		if(!prev && now)
			return true;
		
		else
			return false;
	}

	bool Input::isKeyPressed(GLFWKeys key)
	{
		bool now = Input::singleton()->__keyState[key];
		if (now)
			return true;
		
		else 
			return false;
	}

	bool Input::isKeyReleased(GLFWKeys key)
	{
		bool prev = Input::singleton()->__prevKeyState[key];
		bool now = Input::singleton()->__keyState[key];
		if(!now && prev)
			return true;

		else
			return false;
	}

	void Input::PressKey(int key)
	{
		Input::singleton()->__keyState[key] = true;
	}

	void Input::ReleaseKey(int key)
	{
		Input::singleton()->__keyState[key] = false;
	}
}