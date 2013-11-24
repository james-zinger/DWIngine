#ifndef DWI_MESH
#define DWI_MESH

#include "MeshAsset.h"
#include "MaterialAsset.h"
#include "TextureAsset.h"
#include "Component.h"
#include "DWMath.h"

using std::vector;

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

		/**
		 * @fn	Mesh::Mesh( unsigned int uniqueID, GameObject* gameObject, MeshAsset* meshAsset,
		 * 		MaterialAsset* materialAsset );
		 * @brief	Constructor.
		 * @param	uniqueID			 	Unique identifier.
		 * @param [in,out]	gameObject   	If non-null, the game object.
		 * @param [in,out]	meshAsset	 	If non-null, the mesh asset.
		 * @param [in,out]	materialAsset	If non-null, the material asset.
		 */
		Mesh( unsigned int uniqueID, GameObject* gameObject, MeshAsset* meshAsset, MaterialAsset* materialAsset);
		


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
