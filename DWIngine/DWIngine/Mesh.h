#ifndef DWI_MESH
#define DWI_MESH

#include "MeshAsset.h"
#include "MaterialAsset.h"
#include "Component.h"



namespace DWI
{
	///////////////////////////////////////////////////////////////////////////////////////////////
	class Mesh : public Component
	{

	/////////////////////////////////////////////////////////////
	private:

		/////////////////////////////////////////
		// Private member variables

		MeshAsset*		__meshAsset;
		MaterialAsset*	__materialAsset;


		/////////////////////////////////////////
		// ctor and dtor

		Mesh( unsigned int uniqueID, MeshAsset* meshAsset, MaterialAsset* materialAsset );
		Mesh( unsigned int uniqueID );
		~Mesh( void );



	/////////////////////////////////////////////////////////////
	public:

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
