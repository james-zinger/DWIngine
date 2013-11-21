#include "TextureAsset.h"

#ifndef NULL
#define NULL 0
#endif



///////////////////////////////////////////////////////////////////////////////////////////////
// Public

/////////////////////////////////////////////////////////////
// ctor and dtor

DWI::TextureAsset::TextureAsset( string uniqueName ) : AbstractAsset( uniqueName )
{
	__width = 0;
	__height = 0;
}

DWI::TextureAsset::~TextureAsset( void )
{

}


/////////////////////////////////////////////////////////////
// Getters

int DWI::TextureAsset::height( void )
{
	return __height;
}

vector<unsigned char>& DWI::TextureAsset::imageData( void )
{
	return __imageData;
}

int DWI::TextureAsset::width( void )
{
	return __width;
}


/////////////////////////////////////////////////////////////
// Setters

void DWI::TextureAsset::height( int value )
{
	__height = value;
}

void DWI::TextureAsset::width( int value )
{
	__width = value;
}
