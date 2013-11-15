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

	/////////////////////////////////////////////
	// External callback functions
	extern void error_callback( int error, const char* description );
	extern void key_callback( int key, int action );
	extern void resize_callback( int w, int h );
	extern int windowclose_callback( void );
	extern void windowrefresh_callback( void );
	extern void mousebutton_callback( int button, int action );
	extern void mousepos_callback( int x, int y );
	extern void mousewheel_callback( int pos );

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
		// Private Helper Functions

		bool glLogError( GLenum error );


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
		// Getters

		virtual Camera* getCamera( void );

	};
}

#endif // DWI_OpenGL33Renderer
