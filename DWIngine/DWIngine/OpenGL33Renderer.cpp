#include "OpenGL33Renderer.h"


OpenGL33Renderer::OpenGL33Renderer(void)
{
	if( !glfwInit() )
	{
		LogManager::singleton()->logError("Failed to initalize GLFW\n");
		DWIngine::singleton()->stop();
	}

	

	glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 3);
	glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	if( !glfwOpenWindow( __screenWidth, __screenHeight, 0,0,0,0, 32,0, GLFW_WINDOW ) )
	{
		LogManager::singleton()->logError("Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Update your drivers or use an older version of OpenGL\n" );
		glfwTerminate();
		DWIngine::singleton()->stop();
	}

	// Initialize GLEW
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		LogManager::singleton()->logError("Failed to initialize GLEW\n");
		DWIngine::singleton()->stop();
	}

	glfwSetWindowTitle("Temp");

	glfwEnable( GLFW_STICKY_KEYS );

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	__programID = LoadShaders( "TransformVertexShader.vertexshader", "ColorFragmentShader.fragmentshader" );

	__matrixID = glGetUniformLocation(__programID, "MVP");

	__projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);

	__view = glm::lookAt(
		glm::vec3(4,3,-3), // Camera is at (4,3,-3), in World Space
		glm::vec3(0,0,0), // and looks at the origin
		glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
		);

	__model = glm::mat4(1.0f);

	__mvp = __projection * __view * __model;
	
	glGenVertexArrays(1, &__vertexArrayID);
	glBindVertexArray(__vertexArrayID);
	
	static const GLfloat g_vertex_buffer_data[] = { 
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		 1.0f, 1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,
		 1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		 1.0f,-1.0f,-1.0f,
		 1.0f, 1.0f,-1.0f,
		 1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		 1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		 1.0f,-1.0f, 1.0f,
		 1.0f, 1.0f, 1.0f,
		 1.0f,-1.0f,-1.0f,
		 1.0f, 1.0f,-1.0f,
		 1.0f,-1.0f,-1.0f,
		 1.0f, 1.0f, 1.0f,
		 1.0f,-1.0f, 1.0f,
		 1.0f, 1.0f, 1.0f,
		 1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,
		 1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		 1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		 1.0f,-1.0f, 1.0f
	};

	static const GLfloat g_color_buffer_data[] = { 
		1.0f,  0.0f,  0.0f,
		1.0f,  0.0f,  0.0f,
		1.0f,  0.0f,  0.0f,
		1.0f,  0.0f,  0.0f,
		1.0f,  0.0f,  0.0f,
		1.0f,  0.0f,  0.0f,
		1.0f,  0.0f,  0.0f,
		1.0f,  0.0f,  0.0f,
		1.0f,  0.0f,  0.0f,
		1.0f,  0.0f,  0.0f,
		1.0f,  0.0f,  0.0f,
		1.0f,  0.0f,  0.0f,
		1.0f,  0.0f,  0.0f,
		1.0f,  0.0f,  0.0f,
		1.0f,  0.0f,  0.0f,
		1.0f,  0.0f,  0.0f,
		1.0f,  0.0f,  0.0f,
		1.0f,  0.0f,  0.0f,
		1.0f,  0.0f,  0.0f,
		1.0f,  0.0f,  0.0f,
		1.0f,  0.0f,  0.0f,
		1.0f,  0.0f,  0.0f,
		1.0f,  0.0f,  0.0f,
		1.0f,  0.0f,  0.0f,
		1.0f,  0.0f,  0.0f,
		1.0f,  0.0f,  0.0f,
		1.0f,  0.0f,  0.0f,
		1.0f,  0.0f,  0.0f,
		1.0f,  0.0f,  0.0f,
		1.0f,  0.0f,  0.0f,
		1.0f,  0.0f,  0.0f,
		1.0f,  0.0f,  0.0f,
		1.0f,  0.0f,  0.0f,
		1.0f,  0.0f,  0.0f,
		1.0f,  0.0f,  0.0f,
		1.0f,  0.0f,  0.0f
	};

	glGenBuffers(1, &__vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, __vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_DYNAMIC_DRAW);

	
	glGenBuffers(1, &__colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, __colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);
	
}


OpenGL33Renderer::~OpenGL33Renderer(void)
{
	glfwTerminate();
}

void OpenGL33Renderer::renderPrimitive(Primitive& primative)
{
	
	
	int count = 0;
	switch (primative.type)
	{
	case (PrimitiveType::Tri):
		

		//if(primative.Verticies.size() < 3)
		{
			LogManager::singleton()->logWarn("Unable to render triangle. Not enough verticies");
			return;
		}

		//for (int i = 0; i < primative.Verticies.size(); i++)
		/*{
			primative.vertexBufferData[count] = primative.Verticies[i].x;
			count++;
			primative.vertexBufferData[count] = primative.Verticies[i].y;
			count++;
			primative.vertexBufferData[count] = primative.Verticies[i].z;
			count++;
		}*/

		glBindBuffer(GL_ARRAY_BUFFER, primative.vertexBuffer);
		glVertexAttribPointer(
			0,
			3,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0
		);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glDisableVertexAttribArray(0);
		


		break;
	case (PrimitiveType::Quad):

		break;
	case (PrimitiveType::Cube):

		break;
	};
}

void OpenGL33Renderer::renderMesh(Model& model)
{

}

void OpenGL33Renderer::RenderScene(void)
{

	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(__programID);

	LogManager::singleton()->logTrace("RenderScene Called");
	LogManager::singleton()->logTrace("Primitive Size: " + __primitives.size());
	/*for (int i = 0; i < __primitives.size(); i++)
	{
		renderPrimitive(__primitives[i]);
	}*/


	glUniformMatrix4fv(__matrixID, 1, GL_FALSE, &__mvp[0][0]);

	// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, __vertexbuffer);
		glVertexAttribPointer(
			0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, __colorbuffer);
		glVertexAttribPointer(
			1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
			3,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);

		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, 3*12); // 3 indices starting at 0 -> 1 triangle

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

	glfwSwapBuffers();
}

void OpenGL33Renderer::AddPrimitive(Primitive& primitive)
{
	__primitives.push_back(primitive);
}