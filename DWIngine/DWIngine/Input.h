#ifndef DWI_INPUT
#define DWI_INPUT


#include <unordered_map>
#include "DWMath.h"

using std::unordered_map;
using DWI::Vector2;

namespace DWI
{
	#pragma region GLFWKeys
	/**
	 * Values that represent GLFWKeys.
	 */
	enum GLFWKeys :int
	{
		Key_Space = 32,
		Key_0 = 48,
		Key_1,
		Key_2,
		Key_3,
		Key_4,
		Key_5,
		Key_6,
		Key_7,
		Key_8,
		Key_9,
		Key_A = 65,
		Key_B,
		Key_C,
		Key_D,
		Key_E,
		Key_F,
		Key_G,
		Key_H,
		Key_I,
		Key_J,
		Key_K,
		Key_L,
		Key_M,
		Key_N,
		Key_O,
		Key_P,
		Key_Q,
		Key_R,
		Key_S,
		Key_T,
		Key_U,
		Key_V,
		Key_W,
		Key_X,
		Key_Y,
		Key_Z,
		Key_Esc = 257,
		Key_F1,
		Key_F2,
		Key_F3,
		Key_F4,
		Key_F5,
		Key_F6,
		Key_F7,
		Key_F8,
		Key_F9,
		Key_F10,
		Key_F11,
		Key_F12,
		Key_Up = 283,
		Key_Down,
		Key_Left,
		Key_Right,
		Key_LShift,
		Key_RShift,
		Key_LControl,
		Key_RControl,
		Key_LAlt,
		Key_RAlt,
		Key_Tab,
		Key_Enter,
		Key_BackSpace,
		Key_Insert,
		Key_Delete,
		Key_PageUp,
		Key_PageDown,
		Key_Home,
		Key_End,
		__COUNT = 69
	};
#pragma endregion

	///////////////////////////////////////////////////////////////////////////////////////////////
	class Input
	{
		///////////////////////////////////////////////////////////////////////////
	private:

		///////////////////////////////////////////////////
		// Singleton Member Variable

		static Input*	__singleton;
		
		///////////////////////////////////////////////////
		// Private Member Variables
		unordered_map<int, bool> __keyState;
		unordered_map<int, bool> __prevKeyState;
		unordered_map<int, bool> __mouseButtons;
		unordered_map<int, bool> __prevMouseButtons;

		Vector2 __mousePosition;

		int __mouseWheelIndex;
		int __prevMouseWheelIndex;

		///////////////////////////////////////////////////
		// ctor and dtor

		Input( void );
		~Input( void );


		///////////////////////////////////////////////////////////////////////////
	public:

		void Update( void );

		///////////////////////////////////////////////////
		// Singleton ctor and dtor

		/**
		 * The get singleton method that returns the singleton instance.
		 *
		 * @return	the object of the singleton.
		 */
		static Input* singleton( void );

		/**
		 * Call the destructor on the singleton instance.
		 */
		static void destroySingleton( void );

		////////////////////////////////////////////////////
		// Static Interface functions
		//

		static bool isKeyDown( GLFWKeys key );
		static bool isKeyPressed( GLFWKeys key );
		static bool isKeyReleased( GLFWKeys key );
		static bool GetMouseButtonDown( int button );
		static bool GetMouseButtonPressed( int button );
		static bool GetMouseButtonReleased( int button );

		static void PressKey( int key );
		static void ReleaseKey( int Key );
		static void PressMouseButton( int button );
		static void ReleaseMouseButton( int button );

		static void UpdateMousePosition( Vector2 position );

		static Vector2 MousePosition( void );

		static void UpdateMouseWheelIndex( int index );

		static bool isMouseWheelUp( void );
		static bool isMouseWheelDown( void );
		static int GetMouseWheelIndex( void );
	};
}
#endif // DWI_INPUT