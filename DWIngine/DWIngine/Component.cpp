#include "Component.h"

#ifndef NULL
#define NULL 0
#endif



///////////////////////////////////////////////////////////////////////////////////////////////////
// Public

/////////////////////////////////////////////////////////////////
// ctor and dtor

DWI::Component::Component( unsigned int uniqueID ) : __uniqueID( uniqueID )
{
	__gameObject = NULL;
}

DWI::Component::~Component( void )
{
	// Nothing to release
}


/////////////////////////////////////////////////////////////////
// Getters

DWI::GameObject* DWI::Component::gameObject( void )
{
	return __gameObject;
}

unsigned int DWI::Component::uniqueID( void )
{
	return __uniqueID;
}


/////////////////////////////////////////////////////////////////
// Setters

void DWI::Component::gameObject( DWI::GameObject* value )
{
	__gameObject = value;
}
