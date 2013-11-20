#include "VertexShaderAsset.h"

#ifndef NULL
#define NULL 0
#endif



///////////////////////////////////////////////////////////////////////////////////////////////
// Public

/////////////////////////////////////////////////////////////
// ctor and dtor

DWI::VertexShaderAsset::VertexShaderAsset( string uniqueName, string vertexShader ) : AbstractAsset( uniqueName )
{
	__sourceCode = vertexShader;
}

DWI::VertexShaderAsset::VertexShaderAsset( string uniqueName ) : AbstractAsset( uniqueName )
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

void DWI::VertexShaderAsset::sourceCode( string value )
{
	__sourceCode = value;
}
