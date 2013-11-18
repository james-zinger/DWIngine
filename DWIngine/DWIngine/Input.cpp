#include "Input.h"
/////////////////////////////////////////////////////////////////
// Singleton variable

namespace DWI
{
	Input* Input::__singleton = NULL;

	Input::Input( void )
	{
		for ( int i = GLFWKeys::Key_Space; i < GLFWKeys::__COUNT; i++ )
		{
			__keyState[ i ] = false;
			__prevKeyState[ i ] = false;
		}

		for ( int i = 0; i < 2; i++ )
		{
			__mouseButtons[ i ] = false;
		}

		__mousePosition = Vector2();
	}


	Input::~Input( void )
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
		for ( unordered_map<int, bool>::iterator it = __keyState.begin(); it != __keyState.end(); it++ )
		{
			__prevKeyState[ it->first ] = it->second;
		}

		for ( unordered_map<int, bool>::iterator it = __mouseButtons.begin(); it != __mouseButtons.end(); it++ )
		{
			__prevMouseButtons[ it->first ] = it->second;
		}

		__prevMouseWheelIndex = __mouseWheelIndex;
	}

	bool Input::isKeyDown( GLFWKeys key )
	{
		bool prev = Input::singleton()->__prevKeyState[ key ];
		bool now = Input::singleton()->__keyState[ key ];

		if ( !prev && now )
			return true;

		else
			return false;
	}

	bool Input::isKeyPressed( GLFWKeys key )
	{
		bool now = Input::singleton()->__keyState[ key ];
		if ( now )
			return true;

		else
			return false;
	}

	bool Input::isKeyReleased( GLFWKeys key )
	{
		bool prev = Input::singleton()->__prevKeyState[ key ];
		bool now = Input::singleton()->__keyState[ key ];
		
		if ( !now && prev )
			return true;
		else
			return false;
	}

	bool Input::GetMouseButtonDown( int button )
	{
		bool prev = Input::singleton()->__mouseButtons[ button ];
		bool now = Input::singleton()->__mouseButtons[ button ];

		if ( !prev && now )
			return true;

		else
			return false;

	}

	bool Input::GetMouseButtonPressed( int button )
	{
		bool now = Input::singleton( )->__mouseButtons[ button ];

		if ( now )
			return true;
		else
			return false;
	}

	bool Input::GetMouseButtonReleased( int button )
	{
		bool prev = Input::singleton( )->__mouseButtons[ button ];
		bool now = Input::singleton( )->__mouseButtons[ button ];

		if ( !now && prev )
			return true;
		else
			return false;
		
	}

	void Input::PressKey( int key )
	{
		Input::singleton()->__keyState[ key ] = true;
	}

	void Input::ReleaseKey( int key )
	{
		Input::singleton()->__keyState[ key ] = false;
	}

	void Input::PressMouseButton( int button )
	{
		Input::singleton()->__mouseButtons[ button ] = true;
	}

	void Input::ReleaseMouseButton( int button )
	{
		Input::singleton()->__mouseButtons[ button ] = false;
	}

	void Input::UpdateMousePosition( Vector2 position )
	{
		singleton()->__mousePosition = position;
	}

	Vector2 Input::MousePosition( void )
	{
		return singleton()->__mousePosition;
	}

	void Input::UpdateMouseWheelIndex( int index )
	{
		singleton()->__mouseWheelIndex = index;
	}

	bool Input::isMouseWheelUp( void )
	{
		int diff = singleton()->__mouseWheelIndex - singleton()->__prevMouseWheelIndex;

		if ( diff < 0 )
			return true;
		else
			return false;
	}

	bool Input::isMouseWheelDown( void )
	{
		int diff = singleton()->__mouseWheelIndex - singleton()->__prevMouseWheelIndex;

		if ( diff > 0 )
			return true;
		else
			return false;

	}

	int Input::GetMouseWheelIndex( void )
	{
		return singleton()->__mouseWheelIndex;
	}
}