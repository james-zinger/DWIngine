#ifndef DWI_OpenGL33Renderer
#define DWI_OpenGL33Renderer
#define GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_EXPOSE_NATIVE_WGL
#include "AbstractRenderer.h"
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <map>
#include "Input.h"
#include "GL\glew.h"
#include "GL\glfw.h"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "DWIngine.h"
#include "Log.h"
#include "Model.h"
#include "Camera.h"
#include "shader.hpp"

//#include "glm\gtc\quaternion.hpp"

using namespace glm;
using std::map;


namespace DWI
{

	extern void error_callback (int error, const char* description);

	extern void key_callback (int key, int action);
	///////////////////////////////////////////////////////////////////////////////////////////////
	class OpenGL33Renderer : public AbstractRenderer
	{

	/////////////////////////////////////////////////////////////
	private:

		/////////////////////////////////////////
		// Private member variables

		mat4	__mvp;

		Camera	__cam;
		
		/////////////////////////////////////////
		// Private Callback Functions
		
		
		/////////////////////////////////////////
		// Private Helper Functions

		bool glLogError(GLenum error);
		

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
		// Public Callback functions
		
		
		/////////////////////////////////////////
		// Resize

		virtual void resize( const unsigned int width, const unsigned int height );

	};
}

#endif // DWI_OpenGL33Renderer
