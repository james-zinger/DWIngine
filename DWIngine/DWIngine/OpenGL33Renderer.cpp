#include "ObjectCouldNotBeCreatedException.h"
#include "OpenGL33Renderer.h"
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

void DWI::error_callback(int error, const char* description)
{
	printf(description);
}

void DWI::key_callback(int key, int action)
{
	std::stringstream ss;
	ss << "Key Action: " << key << " -> ";
	
	if (action == GLFW_PRESS)
	{
		ss << "Pressed";
		Input::PressKey(key);
	}
	else if (action == GLFW_RELEASE)
	{
		Input::ReleaseKey(key);
		ss << "Released";
	}
	
	Log::LogInfo(ss.str());
}

bool OpenGL33Renderer::glLogError(GLenum error)
{
	bool result = false;
	while (error != GL_NO_ERROR)
	{
		if (error != GL_INVALID_OPERATION)
		{
			string s = (char*)gluErrorString(error);
			Log::LogError(s);
			error = glGetError();
			result = true;
		}
		
	}
	return result;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Public

/////////////////////////////////////////////////////////////////
// ctor and dtor

OpenGL33Renderer::OpenGL33Renderer( DWI::DWIngine* engine ) : AbstractRenderer( engine )
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
	GLenum error = glGetError();
	if (error =! GL_INVALID_ENUM)
	{
		glLogError(error);
	}

	glfwSetWindowTitle("DWIngine");

	glfwEnable( GLFW_STICKY_KEYS );

	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS); 

	__cam = Camera( vec3(0,0,-10),
				vec3(0,0,0),
				vec3(0,1,0),
				45.0f,
				4.0f/3.0f,
				0.1f,
				1000.0f
			);
	
	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);
	
	vector<vec3> Verts;
	vector<vec2> UVs;
	vector<vec3> Normals;

	loadOBJ("M16_Model.obj", Verts, UVs, Normals); 
	
	registerModel(new Model(__models.size(), "StandardShading.vertexshader", "StandardShading.fragmentshader", "M16.bmp", Verts, UVs, Normals) ); 

	glfwSetKeyCallback(DWI::key_callback);

}

OpenGL33Renderer::~OpenGL33Renderer( void )
{
	glfwTerminate();
}


/////////////////////////////////////////////////////////////////
// Public functions


void OpenGL33Renderer::renderScene(void)
{
	__cam.Update();

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	if(__models.size() > 0)
	{
		int count = 0;
		for (map<int, Model*>::iterator it = __models.begin(); it != __models.end(); it++)
		{

			Model* m = it->second;
			mat4 modelMat = mat4(1.0f);

			mat4 mvp = __cam.getProj() * __cam.getView() * modelMat;

			glBindVertexArray(m->VertexArrayObjectID);

			glUseProgram(m->ShaderProgramID);

			glUniformMatrix4fv(m->ShaderMatrixID, 1, GL_FALSE, &mvp[0][0]);
			glUniformMatrix4fv(m->ShaderModelID, 1, GL_FALSE, &modelMat[0][0]);
			glUniformMatrix4fv(m->ShaderViewID, 1, GL_FALSE, &(__cam.getView())[0][0]);

			vec3 lightPos = vec3(0,2,-2);
			glUniform3f(m->ShaderLightPos, lightPos.x, lightPos.y, lightPos.z);

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, m->Texture);
			glUniform1i(m->TextureID, 0);

			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, m->VertexBuffer);
			glVertexAttribPointer(
				0,
				3,
				GL_FLOAT,
				GL_FALSE,
				0,
				(void*)0
			);

			glEnableVertexAttribArray(1);
			glBindBuffer(GL_ARRAY_BUFFER, m->UVBuffer);
			glVertexAttribPointer(
				1,
				2,
				GL_FLOAT,
				GL_FALSE,
				0,
				(void*)0
			);

			glEnableVertexAttribArray(2);
			glBindBuffer(GL_ARRAY_BUFFER, m->NormalBuffer);
			glVertexAttribPointer(
				2,
				3,
				GL_FLOAT,
				GL_FALSE,
				0,
				(void*)0
			);

			glDrawArrays(GL_TRIANGLES, 0, m->Verts.size());

			glDisableVertexAttribArray(0);
			glDisableVertexAttribArray(1);
			glDisableVertexAttribArray(2);
			count++;
		}
	}
	
	glfwSwapBuffers();
	glLogError(glGetError());

	if(glfwGetKey( GLFW_KEY_F10) == GLFW_PRESS && glfwGetWindowParam( GLFW_OPENED ) )
	{
		__engine->singleton()->stop();
	}

}

void OpenGL33Renderer::resize( const unsigned int width, const unsigned int height )
{
	// TODO
}