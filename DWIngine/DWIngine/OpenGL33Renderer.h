#pragma once
#include "abstractrenderer.h"
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

class OpenGL33Renderer :
	public AbstractRenderer
{

private:
	GLuint __programID;
	GLuint __vertexArrayID;
	GLuint __vertexbuffer;
	GLuint __matrixID;
	GLuint __colorbuffer;

	mat4 __projection;
	mat4 __view;
	mat4 __model;
	mat4 __mvp;

protected:
	virtual void renderMesh(Model& model);
	virtual void renderPrimitive(Primitive& primative);

public:
	OpenGL33Renderer(void);
	~OpenGL33Renderer(void);

	virtual void RenderScene(void);

	virtual void AddPrimitive(Primitive& primitive);


};

