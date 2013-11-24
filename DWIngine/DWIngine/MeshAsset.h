#ifndef DWI_MESHASSET
#define DWI_MESHASSET

#include "DWMath.h"
#include "AbstractAsset.h"
#include <string>
#include <vector>
#include "GL\glew.h"

using std::string;
using std::vector;

namespace DWI
{
	///////////////////////////////////////////////////////////////////////////////////////////////
	class MeshAsset : public AbstractAsset
	{
		friend class OpenGL33Renderer;
		/////////////////////////////////////////////////////////////
	private:

		/////////////////////////////////////////
		// Private member variables

		vector<Vector3> __normals;
		vector<Vector2> __uvs;
		vector<Vector3> __vertices;

		/**
		 * @brief	The vertex array object.
		 */
		GLuint __VAO;

		/**
		 * @brief	The vertex buffer object.
		 */
		GLuint __VBO;

		/**
		 * @brief	The uv buffer object.
		 */
		GLuint __UVBO;

		/**
		 * @brief	The normal buffer object.
		 */
		GLuint __NBO;

		/**
		 * @brief	true if this object is loaded.
		 */
		bool __isLoaded;

		/**
		 * @brief	true if this object is dynamic.
		 */
		bool __isDynamic;

		/**
		 * @fn	void MeshAsset::LoadMeshToGFXCard( bool isDyanmic );
		 * @brief	Loads mesh to graphics card.
		 * @param	isDyanmic	true if this object is dyanmic.
		 */
		void __loadMeshToGFXCard( void );

		/**
		 * @fn	void MeshAsset::UnLoadFromGFXCard();
		 * @brief	Un load from graphics card.
		 */
		void __unLoadFromGFXCard( void );

		/////////////////////////////////////////////////////////////
	public:

		/////////////////////////////////////////
		// ctor and dtor

		MeshAsset( const string uniqueName, bool isDynamic );
		~MeshAsset( void );

		void init( void );

		void LoadGFXVertices( void );

		void LoadGFXNormals( void );

		void LoadGFXUVs( void );

		/////////////////////////////////////////
		// Getters

		vector<Vector3>& normals( void );
		vector<Vector2>& uvs( void );
		vector<Vector3>& vertices( void );

	};
}

#endif // DWI_MESHASSET
