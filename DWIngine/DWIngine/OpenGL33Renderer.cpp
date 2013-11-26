#include "ObjectCouldNotBeCreatedException.h"
#include "OpenGL33Renderer.h"
#include "MeshManager.h"
#include "Scene.h"
#include "TransformManager.h"
#include "Transform.h"
#include "Mesh.h"
#include "Resources.h"
#include "glm\gtc\quaternion.hpp"
#include "glm\gtx\quaternion.hpp"
#ifndef NULL
#define NULL 0
#endif

using namespace glm;
using DWI::OpenGL33Renderer;
using std::iterator;
///////////////////////////////////////////////////////////////////////////////////////////////////
// Private

/////////////////////////////////////////////////////////////////
// Private Callback Functions

void DWI::error_callback( int error, const char* description )
{
	printf( description );
}

void DWI::key_callback( int key, int action )
{
	std::stringstream ss;
	ss << "Key Action: " << key << " -> ";

	if ( action == GLFW_PRESS )
	{
		ss << "Pressed";
		Input::PressKey( key );
	}
	else if ( action == GLFW_RELEASE )
	{
		Input::ReleaseKey( key );
		ss << "Released";
	}

	Log::LogTrace( ss.str() );
}

void DWI::resize_callback( int width, int height )
{
	if ( DWI::DWIngine::isSingletonNull() )
	{
		return;
	}

	stringstream ss;
	ss.clear();
	ss.str( "" );
	ss << "Resize Callback Size: ( " << width << ", " << height << " )";
	Log::LogInfo( ss.str() );
	OpenGL33Renderer* renderer = (OpenGL33Renderer*)DWI::DWIngine::singleton()->renderer();
	//renderer->getCamera()->setAspectRatio( (float)width / (float)height );
	renderer->setScreenDimensions( width, height );
	glViewport( 0, 0, width, height );
}

int DWI::windowclose_callback( void )
{
	DWI::DWIngine::singleton()->stop();
	return GL_FALSE;
}

void DWI::windowrefresh_callback( void )
{
	Log::LogTrace( "Window Refreshed" );
}

/*
 * Left mouse button = 0
 * Right mouse button = 1
 *
 */
void DWI::mousebutton_callback( int button, int action )
{
	stringstream ss;
	ss << "Mouse button action: " << button << " -> ";

	if ( action == GLFW_PRESS )
	{
		ss << "Pressed";
		Input::PressMouseButton( button );
	}
	else
	{
		ss << "Released";
		Input::ReleaseMouseButton( button );
	}

	Log::LogTrace( ss.str() );
}

/**
 * @fn	void DWI::mousepos_callback( int x, int y )
 * @brief	Callback, called when the mouse moves
 * @param	x	The x coordinate.
 * @param	y	The y coordinate.
 */
void DWI::mousepos_callback( int x, int y )
{
	Input::UpdateMousePosition( vec2( x, y ) );
}


/**
 * Callback, called when the mousewheel.
 *
 * @param	pos	The position.
 */
void DWI::mousewheel_callback( int pos )
{
	Input::UpdateMouseWheelIndex( pos );
}

/**
 * Gl log error.
 *
 * @param	error	The error.
 *
 * @return	true if an error occured, false if there is no error.
 */
bool OpenGL33Renderer::glLogError( GLenum error )
{
	bool result = false;
	while ( error != GL_NO_ERROR )
	{

		string s = (char*)gluErrorString( error );
		Log::LogError( s );
		error = glGetError();
		result = true;

	}
	return result;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Public

/////////////////////////////////////////////////////////////////
// ctor and dtor

OpenGL33Renderer::OpenGL33Renderer( DWI::DWIngine* engine ) : AbstractRenderer( engine )
{


	if ( !glfwInit() )
	{
		Log::singleton()->logError( "ObjectCouldNotBeCreatedException >> Failed to initalize GLFW.\n" );
		throw new ObjectCouldNotBeCreatedException( "Failed to initialize GLFW.", this );
	}



	__screenHeight = 400;
	__screenWidth = 600;
	glViewport( 0, 0, __screenWidth, __screenHeight );

	glfwOpenWindowHint( GLFW_FSAA_SAMPLES, 4 );
	glfwOpenWindowHint( GLFW_OPENGL_VERSION_MAJOR, 3 );
	glfwOpenWindowHint( GLFW_OPENGL_VERSION_MINOR, 3 );
	glfwOpenWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );


	// Open a window and create its OpenGL context
	if ( !glfwOpenWindow( __screenWidth, __screenHeight, 0, 0, 0, 0, 32, 0, GLFW_WINDOW ) )
	{
		glfwTerminate();
		Log::singleton()->logError( "ObjectCouldNotBeCreatedException >> Failed to open GLFW window. If you have an Intel GPU, they are not 4.2 compatible. Update your drivers or use an older version of OpenGL.\n" );
		throw new ObjectCouldNotBeCreatedException( "Failed to open GLFW window. If you have an Intel GPU, they are not 4.2 compatible. Update your drivers or use an older version of OpenGL.", this );
	}

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile


	if ( glewInit() != GLEW_OK )
	{
		Log::singleton()->logError( "ObjectCouldNotBeCreatedException >> Failed to Initalize GLEW.\n" );
		throw new ObjectCouldNotBeCreatedException( "Failed to Initalize GLEW.", this );
	}
	GLenum error = glGetError();
	if ( error == !GL_INVALID_ENUM )
	{
		glLogError( error );
	}

	glfwSetWindowTitle( "DWIngine" );

	glfwEnable( GLFW_STICKY_KEYS );

	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

	// Enable depth test
	glEnable( GL_DEPTH_TEST );
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc( GL_LESS );

	__cam = Camera( vec3( 0, 0, -10 ),
					vec3( 0, 0, 0 ),
					vec3( 0, 1, 0 ),
					45.0f,
					(float)__screenWidth / (float)__screenHeight,
					0.1f,
					1000.0f
					);

	// Cull triangles which normal is not towards the camera
	glEnable( GL_CULL_FACE );

	//Setting Callbacks
	glfwSetKeyCallback( key_callback );
	glfwSetWindowSizeCallback( resize_callback );
	glfwSetWindowCloseCallback( windowclose_callback );
	glfwSetWindowRefreshCallback( windowrefresh_callback );
	glfwSetMouseButtonCallback( mousebutton_callback );
	glfwSetMousePosCallback( mousepos_callback );
	glfwSetMouseWheelCallback( mousewheel_callback );

}

OpenGL33Renderer::~OpenGL33Renderer( void )
{
	glfwTerminate();
}


/////////////////////////////////////////////////////////////////
// Public functions


DWI::Camera* OpenGL33Renderer::getCamera( void )
{
	return &__cam;
}

/**
 * Renders the scene.
 */
void OpenGL33Renderer::renderScene( void )
{
	__cam.Update();

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	GameObject* root = DWIngine::singleton()->currentScene()->GetRoot();

	int transformIndex = root->getTransformIndex();

	TransformManager* tm = DWIngine::singleton()->transformManager();

	MeshManager* mm = DWIngine::singleton()->meshManager();

	Transform* t = tm->KeytoPointer( transformIndex );

	int count = 0;

	//Log::LogTrace( "Starting Render Loop" );

	glLogError( glGetError() );

	while ( t->GetNumberOfChildren() != count )
	{
		int childIndex = t->GetChildIndexAtIndex( count );
		Transform* child = tm->KeytoPointer( childIndex );

		GameObject* go = child->gameObject();

		int meshIndex = go->getMeshIndex();

		if ( meshIndex == -1 )
		{
			count++;
			continue;
		}

		Mesh* mesh = mm->KeytoPointer( meshIndex );

		mat4 model = mat4( 1.0f );
		
		mat4 rotation = glm::toMat4( *(child->GetOrientation()) );
		model = translate( model, *(child->GetPosition()) );
		model = model * rotation;
		model = scale( model, *(child->GetScale()) );
		
		mat4 mvp = __cam.getProj() * __cam.getView() * model;

		MeshAsset* meshAsset = mesh->meshAsset();

		MaterialAsset* matAsset = DWIngine::singleton()->resources()->getMaterial( mesh->__materialAsset );

		glBindVertexArray( meshAsset->__VAO );
		
		//glLogError( glGetError() );
		//Log::LogTrace( "Checking For Errors 1" );

		glUseProgram( matAsset->__shaderProgramID );

	
		//glLogError( glGetError() );
		//Log::LogTrace( "Checking For Errors 2" );

		glUniformMatrix4fv( matAsset->__shaderMatrixID, 1, GL_FALSE, &mvp[ 0 ][ 0 ] );
		glUniformMatrix4fv( matAsset->__shaderModelID, 1, GL_FALSE, &model[ 0 ][ 0 ] );
		glUniformMatrix4fv( matAsset->__shaderViewID, 1, GL_FALSE, &(__cam.getView())[0][0]);
		
		//glLogError( glGetError() );
		//Log::LogTrace( "Checking For Errors 3" );

		vec3 lightPos = vec3( 0, 2, -5 );

		glUniform3f( matAsset->__shaderLightPos, lightPos.x, lightPos.y, lightPos.z );


		glActiveTexture( GL_TEXTURE0 );
		glBindTexture( GL_TEXTURE_2D, matAsset->__texture );
		glUniform1i( matAsset->__textureShaderID, 0 );

		//glLogError( glGetError() );
		//Log::LogTrace( "Checking For Errors 4" );

		glEnableVertexAttribArray( 0 );
		glBindBuffer( GL_ARRAY_BUFFER, meshAsset->__VBO );
		glVertexAttribPointer(
			0,
			3,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0
			);

		glEnableVertexAttribArray( 1 );
		glBindBuffer( GL_ARRAY_BUFFER, meshAsset->__UVBO );
		glVertexAttribPointer(
			1,
			2,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0
			);

		glEnableVertexAttribArray( 2 );
		glBindBuffer( GL_ARRAY_BUFFER, meshAsset->__NBO );
		glVertexAttribPointer(
			2,
			3,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0
			);

		glDrawArrays( GL_TRIANGLES, 0, meshAsset->__vertices.size()  );

		glDisableVertexAttribArray( 0 );
		glDisableVertexAttribArray( 1 );
		glDisableVertexAttribArray( 2 );

		count++;

	}

	glfwSwapBuffers();
	glLogError( glGetError() );

	if ( glfwGetKey( GLFW_KEY_F10 ) == GLFW_PRESS && glfwGetWindowParam( GLFW_OPENED ) )
	{
		__engine->singleton()->stop();
	}

}
