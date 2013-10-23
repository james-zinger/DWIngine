#include "Primitive.h"
#include "LogManager.h"



///////////////////////////////////////////////////////////////////////////////////////////////
// Public

/////////////////////////////////////////////////////////////
// ctor and dtor

DWI::Primitive::Primitive( void )
{
}

DWI::Primitive::Primitive( PrimitiveType type )
{
	this->type = type;
}

DWI::Primitive::Primitive( PrimitiveType type, glm::vec3* verts, glm::vec3* vertnormals )
{
	this->type = type;
	this->Verticies = verts;
	this->VertexNormals = vertnormals;

	int count = 0;
	
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof (vertexBufferData),vertexBufferData, GL_DYNAMIC_DRAW);
}

DWI::Primitive::~Primitive( void )
{

}
