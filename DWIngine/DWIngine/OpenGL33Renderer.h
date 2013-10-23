#ifndef DWI_OpenGL33Renderer
#define DWI_OpenGL33Renderer

#include "AbstractRenderer.h"
#include <stdio.h>
#include <stdlib.h>
#include "GL\glew.h"
#include "GL\glfw.h"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "DWIngine.h"
#include "LogManager.h"
#include "shader.hpp"
#include "glm\gtc\quaternion.hpp"

using namespace glm;



namespace DWI
{
	///////////////////////////////////////////////////////////////////////////////////////////////
	class OpenGL33Renderer : public AbstractRenderer
	{

	/////////////////////////////////////////////////////////////
	private:

		/////////////////////////////////////////
		// Private member variables

		GLuint	__programID;
		GLuint	__vertexArrayID;
		GLuint	__vertexbuffer;
		GLuint	__matrixID;
		GLuint	__colorbuffer;

		mat4	__projection;
		mat4	__view;
		mat4	__model;
		mat4	__mvp;


	/////////////////////////////////////////////////////////////
	protected:

		/////////////////////////////////////////
		// Protected render functions

		virtual void renderMesh( Mesh& model );


	/////////////////////////////////////////////////////////////
	public:

		/////////////////////////////////////////
		// ctor and dtor

		OpenGL33Renderer( DWIngine* engine );
		virtual ~OpenGL33Renderer( void );


		/////////////////////////////////////////
		// Public render functions

		virtual void renderScene( void );


		/////////////////////////////////////////
		// Resize

		virtual void resize( const unsigned int width, const unsigned int height );

	};
}

#endif // DWI_OpenGL33Renderer
