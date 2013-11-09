#include "FileCouldNotBeOpenedException.h"

#ifndef NULL
#define NULL 0
#endif



///////////////////////////////////////////////////////////////////////////////////////////////////
// Public

/////////////////////////////////////////////////////////////////
// ctor and dtor

DWI::FileCouldNotBeOpenedException::FileCouldNotBeOpenedException( void ) : exception( "Somthing went wrong with a file open!" )
{
	__context = NULL;
}

DWI::FileCouldNotBeOpenedException::FileCouldNotBeOpenedException( const string message ) : exception( message.c_str() )
{
	__context = NULL;
}

DWI::FileCouldNotBeOpenedException::FileCouldNotBeOpenedException( const string message, const void* context ) : exception( message.c_str() )
{
	__context = context;
}

DWI::FileCouldNotBeOpenedException::~FileCouldNotBeOpenedException( void )
{
	// No resources to release
}
