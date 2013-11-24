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

	Mesh::Mesh( const unsigned int uniqueID, GameObject* gameObject, string meshAsset, string matAsset) : Component( uniqueID, gameObject )
	{
		__meshAsset = meshAsset;
		__materialAsset = matAsset;
	}

	Mesh::~Mesh( void )
	{
		__meshAsset = "";
		__materialAsset = "";
	}

	MeshAsset* Mesh::meshAsset( void )
	{
		return DWIngine::singleton()->resources()->getMesh( __meshAsset );
	}

	MaterialAsset* Mesh::materialAsset( void )
	{
		return DWIngine::singleton()->resources()->getMaterial( __materialAsset );
	}
	
}
