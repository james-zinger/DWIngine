#include "ObjectCouldNotBeCreatedException.h"

#ifndef NULL
#define NULL 0
#endif



///////////////////////////////////////////////////////////////////////////////////////////////////
// Public

/////////////////////////////////////////////////////////////////
// ctor and dtor

DWI::ObjectCouldNotBeCreatedException::ObjectCouldNotBeCreatedException( void ) : exception( "Somthing went wrong with object creation!" )
{
	__context = NULL;
}

DWI::ObjectCouldNotBeCreatedException::ObjectCouldNotBeCreatedException( const string message ) : exception( message.c_str() )
{
	__context = NULL;
}

DWI::ObjectCouldNotBeCreatedException::ObjectCouldNotBeCreatedException( const string message, const void* context ) : exception( message.c_str() )
{
	__context = context;
}

DWI::ObjectCouldNotBeCreatedException::~ObjectCouldNotBeCreatedException( void )
{
	// No resources to release
}
