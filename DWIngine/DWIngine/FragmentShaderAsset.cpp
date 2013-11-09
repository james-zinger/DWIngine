#include "FragmentShaderAsset.h"

#ifndef NULL
#define NULL 0
#endif



///////////////////////////////////////////////////////////////////////////////////////////////
// Public

/////////////////////////////////////////////////////////////
// ctor and dtor

DWI::FragmentShaderAsset::FragmentShaderAsset( const string uniqueName, const string fragmentShader ) : AbstractAsset( uniqueName )
{
	__sourceCode = fragmentShader;
}

DWI::FragmentShaderAsset::FragmentShaderAsset( const string uniqueName ) : AbstractAsset( uniqueName )
{
	__sourceCode = "";
}

DWI::FragmentShaderAsset::~FragmentShaderAsset( void )
{

}


/////////////////////////////////////////////////////////////
// Getters

string DWI::FragmentShaderAsset::sourceCode( void )
{
	return __sourceCode;
}


/////////////////////////////////////////////////////////////
// Setters

void DWI::FragmentShaderAsset::sourceCode( const string value )
{
	__sourceCode = value;
}
