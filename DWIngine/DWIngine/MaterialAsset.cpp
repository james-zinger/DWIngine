#include "MaterialAsset.h"

#ifndef NULL
#define NULL 0
#endif



///////////////////////////////////////////////////////////////////////////////////////////////
// Public

/////////////////////////////////////////////////////////////
// ctor and dtor

DWI::MaterialAsset::MaterialAsset( string uniqueName, string fragmentShaderName, string vertexShaderName, string textureName ) : AbstractAsset( uniqueName )
{
	__fragmentShaderUniqueName = fragmentShaderName;
	__textureUniqueName = textureName;
	__vertexShaderUniqueName = vertexShaderName;
}

DWI::MaterialAsset::MaterialAsset( string uniqueName ) : AbstractAsset( uniqueName )
{
	__fragmentShaderUniqueName = "";
	__textureUniqueName = "";
	__vertexShaderUniqueName = "";
}

DWI::MaterialAsset::~MaterialAsset( void )
{

}


/////////////////////////////////////////////////////////////
// Getters

string DWI::MaterialAsset::fragmentShaderUniqueName( void )
{
	return __fragmentShaderUniqueName;
}

string DWI::MaterialAsset::textureUniqueName( void )
{
	return __textureUniqueName;
}

string DWI::MaterialAsset::vertexShaderUniqueName( void )
{
	return __vertexShaderUniqueName;
}


/////////////////////////////////////////////////////////////
// Setters

void DWI::MaterialAsset::fragmentShaderUniqueName( string value )
{
	__fragmentShaderUniqueName = value;
}

void DWI::MaterialAsset::textureUniqueName( string value )
{
	__textureUniqueName = value;
}

void DWI::MaterialAsset::vertexShaderUniqueName( string value )
{
	__vertexShaderUniqueName = value;
}
