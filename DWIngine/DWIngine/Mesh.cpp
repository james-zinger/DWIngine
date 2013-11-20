#include "Mesh.h"

#ifndef NULL
#define NULL 0
#endif



///////////////////////////////////////////////////////////////////////////////////////////////////
// Private

/////////////////////////////////////////////////////////////////
// ctor and dtor

DWI::Mesh::Mesh( unsigned int uniqueID, MeshAsset* meshAsset, MaterialAsset* materialAsset ) : Component( uniqueID )
{
	__meshAsset = meshAsset;
	__materialAsset = materialAsset;
}

DWI::Mesh::Mesh( unsigned int uniqueID ) : Component( uniqueID )
{
	__meshAsset = NULL;
	__materialAsset = NULL;
}

DWI::Mesh::~Mesh(void)
{

}
