#include "TextAsset.h"

#ifndef NULL
#define NULL 0
#endif



///////////////////////////////////////////////////////////////////////////////////////////////
// Public

/////////////////////////////////////////////////////////////
// ctor and dtor

DWI::TextAsset::TextAsset( string uniqueName, string text ) : AbstractAsset( uniqueName )
{
	__text = text;
}

DWI::TextAsset::TextAsset( string uniqueName ) : AbstractAsset( uniqueName )
{
	__text = "";
}

DWI::TextAsset::~TextAsset( void )
{

}


/////////////////////////////////////////////////////////////
// Getters

string DWI::TextAsset::text( void )
{
	return __text;
}


/////////////////////////////////////////////////////////////
// Setters

void DWI::TextAsset::text( const string value )
{
	__text = value;;
}
