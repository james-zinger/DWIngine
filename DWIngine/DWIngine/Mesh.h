#ifndef DWI_MESH
#define DWI_MESH

#include "MeshAsset.h"
#include "MaterialAsset.h"
#include "Component.h"
#include "DWMath.h"

namespace DWI
{
	///////////////////////////////////////////////////////////////////////////////////////////////
	class Mesh : public Component
	{
		friend class MeshManager;
	/////////////////////////////////////////////////////////////
	private:

		/////////////////////////////////////////
		// Private member variables

		MeshAsset*		__meshAsset;
		MaterialAsset*	__materialAsset;


		/////////////////////////////////////////
		// ctor 

		Mesh( unsigned int uniqueID, GameObject* gameObject, MeshAsset* meshAsset, MaterialAsset* materialAsset );
		


	/////////////////////////////////////////////////////////////
	public:
		/////////////////////////////////////////
		// dtor
		~Mesh( void );


		/////////////////////////////////////////
		// Getters

		/*
		* The mesh asset this mesh uses for its geometry.
		*/
		MeshAsset* meshAsset( void );

		/*
		* The material asset this mesh uses for its shaders and texture.
		*/
		MaterialAsset* materialAsset( void );

	};
}

#endif // DWI_MESH
