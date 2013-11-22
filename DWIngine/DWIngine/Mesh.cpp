#include "Mesh.h"
#include "DWIngine.h"
#include "MeshManager.h"
#ifndef NULL
#define NULL 0
#endif


namespace DWI
{
	///////////////////////////////////////////////////////////////////////////////////////////////////
	// Private

	/////////////////////////////////////////////////////////////////
	// ctor and dtor

	Mesh::Mesh( const unsigned int uniqueID, GameObject* gameObject, MeshAsset* meshAsset, MaterialAsset* matAsset) : Component( uniqueID, gameObject )
	{
		__meshAsset = meshAsset;
		__materialAsset = matAsset;
	}

	Mesh::~Mesh( void )
	{
		__meshAsset = NULL;
		__materialAsset = NULL;
	}
	
}
