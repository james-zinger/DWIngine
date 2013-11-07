#include "ObjectCouldNotBeCreatedException.h"
#include "OpenGL33Renderer.h"

#ifndef NULL
#define NULL 0
#endif

using namespace glm;


///////////////////////////////////////////////////////////////////////////////////////////////////
// Private

/////////////////////////////////////////////////////////////////
// Private Callback Functions

void DWI::error_callback(int error, const char* description)
{
	printf(description);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Protected

/////////////////////////////////////////////////////////////////
// Protected render functions

void DWI::OpenGL33Renderer::renderMesh( Mesh& model )
{
	
}


///////////////////////////////////////////////////////////////////////////////////////////////////
// Public

/////////////////////////////////////////////////////////////////
// ctor and dtor

DWI::OpenGL33Renderer::OpenGL33Renderer( DWI::DWIngine* engine ) : AbstractRenderer( engine )
{

	
	if( !glfwInit() )
	{
		Log::singleton()->logError( "ObjectCouldNotBeCreatedException >> Failed to initalize GLFW.\n" );
		throw new ObjectCouldNotBeCreatedException( "Failed to initialize GLFW.", this );
	}

	
	
	__screenHeight = 400;
	__screenWidth = 600;

	glfwOpenWindowHint( GLFW_FSAA_SAMPLES, 4 );
	glfwOpenWindowHint( GLFW_OPENGL_VERSION_MAJOR, 3 );
	glfwOpenWindowHint( GLFW_OPENGL_VERSION_MINOR, 3 );
	glfwOpenWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );


	// Open a window and create its OpenGL context
	if ( !glfwOpenWindow(__screenWidth, __screenHeight, 0, 0, 0, 0, 32 ,0, GLFW_WINDOW ) )
	{
		glfwTerminate();
		Log::singleton()->logError( "ObjectCouldNotBeCreatedException >> Failed to open GLFW window. If you have an Intel GPU, they are not 4.2 compatible. Update your drivers or use an older version of OpenGL.\n" );
		throw new ObjectCouldNotBeCreatedException( "Failed to open GLFW window. If you have an Intel GPU, they are not 4.2 compatible. Update your drivers or use an older version of OpenGL.", this );
	}
	
	// Initialize GLEW
	glewExperimental = true; // Needed for core profile



	if (glewInit() != GLEW_OK) {
		Log::singleton()->logError( "ObjectCouldNotBeCreatedException >> Failed to Initalize GLEW.\n" );
		throw new ObjectCouldNotBeCreatedException( "Failed to Initalize GLEW.", this );
	}
	
	glfwSetWindowTitle("DWIngine");

	glfwEnable( GLFW_STICKY_KEYS );

	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS); 

	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);

	glGenVertexArrays(1, &__vertexArrayID);
	glBindVertexArray(__vertexArrayID);

	__programID = LoadShaders( "TransformVertexShader.vertexshader", "ColorFragmentShader.fragmentshader" );

	__matrixID = glGetUniformLocation( __programID, "MVP" );

	__projection = glm::perspective( 45.0f, 4.0f / 3.0f, 0.1f, 100.0f );

	__view = glm::lookAt(
		glm::vec3(  4,  3, -3 ), // Camera is at ( 4, 3, -3 ), in World Space
		glm::vec3(  0,  0,  0 ), // and looks at the origin
		glm::vec3(  0,  1,  0 )  // Head is up (set to 0, -1, 0 to look upside-down)
	);

	__model = glm::mat4( 1.0f );

	__mvp = __projection * __view * __model;
	
	glUseProgram(__programID);
}


DWI::OpenGL33Renderer::~OpenGL33Renderer( void )
{
	glfwTerminate();
}


/////////////////////////////////////////////////////////////////
// Public functions

void DWI::OpenGL33Renderer::renderScene(void)
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	

}

void DWI::OpenGL33Renderer::resize( const unsigned int width, const unsigned int height )
{
	// TODO
}