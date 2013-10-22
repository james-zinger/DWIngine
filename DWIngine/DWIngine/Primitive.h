#pragma once

#include "GL\glew.h"
#include "GL\glfw.h"
#include "glm\glm.hpp"
#include <vector>
using namespace std;
enum PrimitiveType
{
	Quad,
	Tri,
	Cube
};

class Primitive
{
	
public:

	//Ctors
	Primitive(void);
	Primitive(PrimitiveType type);
	Primitive(PrimitiveType type, glm::vec3 verts[24], glm::vec3 vertnormals[24]);


	//Dtors
	~Primitive(void);

	//Members
	PrimitiveType type;
	glm::vec3* Verticies;
	glm::vec3* VertexNormals;
	glm::vec3* VertexColors;
	GLuint vertexBuffer;
	GLfloat vertexBufferData[24];
};

