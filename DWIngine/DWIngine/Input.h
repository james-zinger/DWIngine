#ifndef DWI_INPUT
#define DWI_INPUT

#include <map>

using std::map;

namespace DWI
{
enum GLFWKeys:int
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
	Key_Esc = 256,
	Key_Enter,
	Key_Tab,
	Key_BackSpace,
	Key_Insert,
	Key_Delete,
	Key_Right,
	Key_Left,
	Key_Down,
	Key_Up,
	Key_PageUp,
	Key_PageDown,
	Key_Home,
	Key_End,
	Key_F1 = 290,
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
	Key_LShift = 340,
	Key_LControl,
	Key_LAlt,
	Key_LSuper,
	Key_RShift,
	Key_RControl,
	Key_RAlt,
	Key_RSuper,
	__COUNT = 71
};

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
		map<int, bool> __keyState;
		map<int, bool> __prevKeyState;

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
		* The get singleton method that returns the singleton instance
		* @return the object of the singleton
		*/
		static Input* singleton( void );

		/**
		* Call the destructor on the singleton instance
		*/
		static void destroySingleton( void );

		////////////////////////////////////////////////////
		// Static Interface functions
		static bool isKeyDown(GLFWKeys key);
		static bool isKeyPressed(GLFWKeys key);
		static bool isKeyReleased(GLFWKeys key);
	
		static void PressKey(int key);
		static void ReleaseKey(int Key);
	};
}
#endif // DWI_INPUT