#include "Model.h"


using DWI::Model;
///////////////////////////////////////////////////////////////////////////////////////////////////
// Private

/////////////////////////////////////////////////////////////////
// ctor and dtor

Model::Model( int ID, string vertexShaderPath, string fragmentShaderPath, string texturePath, vector<vec3> Verts, vector<vec2> UVs, vector<vec3> Normals )
{
	modelID = ID;
	glGenVertexArrays(1, &VertexArrayObjectID);
	glBindVertexArray(VertexArrayObjectID);

	ShaderProgramID = LoadShaders(vertexShaderPath.c_str(), fragmentShaderPath.c_str());

	ShaderMatrixID = glGetUniformLocation(ShaderProgramID, "MVP");
	ShaderViewID = glGetUniformLocation(ShaderProgramID, "V");
	ShaderModelID = glGetUniformLocation(ShaderProgramID, "M");
	ShaderLightPos = glGetUniformLocation(ShaderProgramID, "LightPosition_worldspace");

	Texture = loadBMP_custom(texturePath.c_str());
	TextureID = glGetUniformLocation(ShaderProgramID, "TextureSampler");


	this->Verts = Verts;
	this->Normals = Normals;
	this->UVs = UVs;

	glGenBuffers(1, &VertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, Verts.size() * sizeof(vec3), &Verts[0], GL_STATIC_DRAW);

	glGenBuffers(1, &UVBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, UVBuffer);
	glBufferData(GL_ARRAY_BUFFER, UVs.size() * sizeof(vec2), &UVs[0], GL_STATIC_DRAW);

	glGenBuffers(1, &NormalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, NormalBuffer);
	glBufferData(GL_ARRAY_BUFFER, Normals.size() * sizeof(vec3), &Normals[0], GL_STATIC_DRAW);
}

Model::~Model( void )
{
	glDeleteBuffers(1, &VertexBuffer);
	glDeleteBuffers(1, &UVBuffer);
	glDeleteBuffers(1, &NormalBuffer);
	glDeleteProgram(ShaderProgramID);
	glDeleteTextures(1, &Texture);
	glDeleteVertexArrays(1, &VertexArrayObjectID);
}

int Model::getID( void )
{
	return modelID;
}

