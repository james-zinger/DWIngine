#ifndef DWI_PRIMITIVE
#define DWI_PRIMITIVE

#include "GL\glew.h"
#include "GL\glfw.h"
#include "glm\glm.hpp"
#include <vector>



namespace DWI
{
	///////////////////////////////////////////////////////////////////////////////////////////////
	enum PrimitiveType
	{
		Quad,
		Tri,
		Cube
	};


	///////////////////////////////////////////////////////////////////////////////////////////////
	class Primitive
	{
	
	/////////////////////////////////////////////////////////////
	public:

		/////////////////////////////////////////
		// Public member variables

		PrimitiveType type;
		glm::vec3* Verticies;
		glm::vec3* VertexNormals;
		glm::vec3* VertexColors;
		GLuint vertexBuffer;
		GLfloat vertexBufferData[24];


		/////////////////////////////////////////
		// ctor and dtor

		Primitive( void );
		Primitive( PrimitiveType type );
		Primitive( PrimitiveType type, glm::vec3 verts[24], glm::vec3 vertnormals[24] );
		~Primitive( void );
	};
}

#endif // DWI_PRIMITIVE
