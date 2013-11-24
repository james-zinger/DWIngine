#include "DWMath.h"
#include "MeshAsset.h"

#ifndef NULL
#define NULL 0
#endif

namespace DWI
{

	///////////////////////////////////////////////////////////////////////////////////////////////
	// Public

	/////////////////////////////////////////////////////////////
	// ctor and dtor

	MeshAsset::MeshAsset( string uniqueName ) : AbstractAsset( uniqueName )
	{
		__isLoaded = false;
	}

	MeshAsset::~MeshAsset( void )
	{
		__unLoadFromGFXCard();
	}

	void MeshAsset::__loadMeshToGFXCard( bool isDyanmic )
	{
		if ( !__isLoaded )
		{
			// Vertex Object Array Generation
			glGenVertexArrays( 1, &__VAO );
			glBindVertexArray( __VAO );


			// Vertex Buffer Object
			glGenBuffers( 1, &__VBO );
			glBindBuffer( GL_ARRAY_BUFFER, __VBO );

			if ( isDyanmic )
			{
				glBufferData( GL_ARRAY_BUFFER, __vertices.size() * sizeof( Vector3 ), &__vertices[ 0 ], GL_DYNAMIC_DRAW );
			}
			else
			{
				glBufferData( GL_ARRAY_BUFFER, __vertices.size() * sizeof( Vector3 ), &__vertices[ 0 ], GL_STATIC_DRAW );
			}



			// uv Buffer Object
			glGenBuffers( 1, &__UVBO );
			glBindBuffer( GL_ARRAY_BUFFER, __UVBO );

			if ( isDyanmic )
			{
				glBufferData( GL_ARRAY_BUFFER, __uvs.size() * sizeof( Vector2 ), &__uvs[ 0 ], GL_DYNAMIC_DRAW );
			}
			else
			{
				glBufferData( GL_ARRAY_BUFFER, __uvs.size() * sizeof( Vector2 ), &__uvs[ 0 ], GL_STATIC_DRAW );
			}

			// normal Buffer Object
			glGenBuffers( 1, &__NBO );
			glBindBuffer( GL_ARRAY_BUFFER, __NBO );

			if ( isDyanmic )
			{
				glBufferData( GL_ARRAY_BUFFER, __normals.size() * sizeof( Vector3 ), &__normals[ 0 ], GL_DYNAMIC_DRAW );
			}
			else
			{
				glBufferData( GL_ARRAY_BUFFER, __normals.size() * sizeof( Vector3 ), &__normals[ 0 ], GL_STATIC_DRAW );
			}

			__isLoaded = !__isLoaded;
		}
	}

	void MeshAsset::__unLoadFromGFXCard( void )
	{
		if ( __isLoaded )
		{
			glDeleteBuffers( 1, &__VBO );
			glDeleteBuffers( 1, &__UVBO );
			glDeleteBuffers( 1, &__NBO );
			glDeleteVertexArrays( 1, &__VAO );

			__isLoaded = !__isLoaded;
		}
	}

	/////////////////////////////////////////////////////////////
	// Getters

	vector<Vector3>& DWI::MeshAsset::normals( void )
	{
		return __normals;
	}

	vector<Vector2>& DWI::MeshAsset::uvs( void )
	{
		return __uvs;
	}

	vector<Vector3>& DWI::MeshAsset::vertices( void )
	{
		return __vertices;
	}

}