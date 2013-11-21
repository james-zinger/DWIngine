#include "Mesh.h"
#include "GameObject.h"
#ifndef NULL
#define NULL 0
#endif


namespace DWI
{
	///////////////////////////////////////////////////////////////////////////////////////////////////
	// Private

	/////////////////////////////////////////////////////////////////
	// ctor and dtor

	Mesh::Mesh( const unsigned int uniqueID, GameObject* gameObject ) : Component( uniqueID, gameObject )
	{

	}

	Mesh::~Mesh( void )
	{

	}
}
