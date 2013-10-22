#include "Primitive.h"
#include "LogManager.h"

Primitive::Primitive(void)
{
}

Primitive::Primitive(PrimitiveType type)
{
	this->type = type;
}

Primitive::Primitive(PrimitiveType type, glm::vec3* verts, glm::vec3* vertnormals)
{
	this->type = type;
	this->Verticies = verts;
	this->VertexNormals = vertnormals;

	int count = 0;
	

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof (vertexBufferData),vertexBufferData, GL_DYNAMIC_DRAW);
}


Primitive::~Primitive(void)
{
}
