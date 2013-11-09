#include "TextureAsset.h"

#ifndef NULL
#define NULL 0
#endif



///////////////////////////////////////////////////////////////////////////////////////////////
// Public

/////////////////////////////////////////////////////////////
// ctor and dtor

DWI::TextureAsset::TextureAsset( const string uniqueName, unsigned char* data ) : AbstractAsset( uniqueName )
{
	__imageData = data;
}

DWI::TextureAsset::TextureAsset( const string uniqueName ) : AbstractAsset( uniqueName )
{
	__imageData = NULL;
}

DWI::TextureAsset::~TextureAsset( void )
{
	if ( __imageData != NULL )
	{
		delete __imageData;
	}
}


/////////////////////////////////////////////////////////////
// Getters

unsigned char* DWI::TextureAsset::imageData( void )
{
	return __imageData;
}


/////////////////////////////////////////////////////////////
// Setters

void DWI::TextureAsset::imageData( unsigned char* value )
{
	__imageData = value;
}
