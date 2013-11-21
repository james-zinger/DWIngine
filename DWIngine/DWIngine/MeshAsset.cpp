#include "DWMath.h"
#include "MeshAsset.h"

#ifndef NULL
#define NULL 0
#endif

using std::vector;



///////////////////////////////////////////////////////////////////////////////////////////////
// Public

/////////////////////////////////////////////////////////////
// ctor and dtor

DWI::MeshAsset::MeshAsset( string uniqueName ) : AbstractAsset( uniqueName )
{

}

DWI::MeshAsset::~MeshAsset( void )
{

}


/////////////////////////////////////////////////////////////
// Getters

vector<DWI::Vector3>& DWI::MeshAsset::normals( void )
{
	return __normals;
}

vector<DWI::Vector2>& DWI::MeshAsset::uvs( void )
{
	return __uvs;
}

vector<DWI::Vector3>& DWI::MeshAsset::vertices( void )
{
	return __vertices;
}
