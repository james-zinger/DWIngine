#ifndef DWI_TRANSFORM
#define DWI_TRANSFORM

#include "Component.h"



namespace DWI
{
	///////////////////////////////////////////////////////////////////////////////////////////////
	class Transform : public Component
	{

	// The SceneManager manages all Transforms in the scene. Look to this class for functionality for
	// instantiation and destruction of Transforms and any other sensitive process.
	friend class SceneManager;


	/////////////////////////////////////////////////////////////////
	private:

		/////////////////////////////////////////////
		// Private member variables




		/////////////////////////////////////////////
		// ctor and dtor

		Transform( const unsigned int uniqueID );
		~Transform( void );


	/////////////////////////////////////////////////////////////////
	public:

		

	};
}

#endif // DWI_TRANSFORM
