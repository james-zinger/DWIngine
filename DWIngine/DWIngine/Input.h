#ifndef DWI_INPUT
#define DWI_INPUT

#include "OIS\OISInputManager.h"
#include "OIS\OISException.h"
#include "OIS\OISKeyboard.h"
#include "OIS\OISMouse.h"
#include "OIS\OISEvents.h"



namespace DWI
{
	using OIS::InputManager;
	using OIS::Mouse;
	using OIS::Keyboard;
	using OIS::ParamList;
	///////////////////////////////////////////////////////////////////////////////////////////////
	class Input
	{

	///////////////////////////////////////////////////////////////////////////
	private:
		
		///////////////////////////////////////////////////
		// Singleton Member Variable

		Input*			__singleton;

		///////////////////////////////////////////////////
		// Private Member Variables

		InputManager*	__inputManager;
		Mouse*			__mouse;
		Keyboard*		__keyboard;

		///////////////////////////////////////////////////
		// ctor and dtor

		Input( void );
		~Input( void );


	///////////////////////////////////////////////////////////////////////////
	public:
		
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
		static void destorySingletion( void );

		///////////////////////////////////////////////////
		// getters for private members

		/**
		* Returns the pointer to the OIS mouse object
		* @returns Pointer to mouse object
		*/
		Mouse* GetMouse( void );

		/**
		* Returns the pointer to the OIS keyboard object
		* @returns Pointer to the keyboard object
		*/
		Keyboard* GetKeyboard( void );

		/**
		* Returns the pointer to the OIS input manager
		* @returns Pointer to the Inputmanager Object
		*/
		InputManager* GetInputManager( void );
	

	};
}
#endif // DWI_INPUT