#include "VertexShaderAsset.h"

#ifndef NULL
#define NULL 0
#endif



///////////////////////////////////////////////////////////////////////////////////////////////
// Public

/////////////////////////////////////////////////////////////
// ctor and dtor

DWI::VertexShaderAsset::VertexShaderAsset( const string uniqueName, const string vertexShader ) : AbstractAsset( uniqueName )
{
	__sourceCode = vertexShader;
}

DWI::VertexShaderAsset::VertexShaderAsset( const string uniqueName ) : AbstractAsset( uniqueName )
{
	__sourceCode = "";
}

DWI::VertexShaderAsset::~VertexShaderAsset( void )
{

}


/////////////////////////////////////////////////////////////
// Getters

string DWI::VertexShaderAsset::sourceCode( void )
{
	return __sourceCode;
}


/////////////////////////////////////////////////////////////
// Setters

void DWI::VertexShaderAsset::sourceCode( const string value )
{
	__sourceCode = value;
}
