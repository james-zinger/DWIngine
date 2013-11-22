#ifndef DWI_MODEL
#define DWI_MODEL

#include <vector>
#include <string>
#include <map>
#include "glm\glm.hpp"
#include "GL\glew.h"
#include "shader.hpp"
#include "objloader.hpp"
#include "texture.hpp"

using std::vector;
using std::string;
using std::map;
using glm::vec3;
using glm::vec2;
namespace DWI
{
	
	///////////////////////////////////////////////////////////////////////////////////////////////
	class Model
	{
	private:
		int modelID;
	/////////////////////////////////////////////////////////////
	public:

		/////////////////////////////////////////
		// ctor and dtor

		Model( int ID, string vertexShaderPath, string fragmentShaderPath, string texturePath, vector<vec3> Verts, vector<vec2> UVs, vector<vec3> Normals );
		~Model( void );

		/////////////////////////////////////////
		// Public Members

		GLuint ShaderProgramID;
		GLuint ShaderMatrixID;
		GLuint ShaderViewID;
		GLuint ShaderModelID;
		GLuint ShaderLightPos;
		GLuint VertexArrayObjectID;
		GLuint VertexBuffer;
		GLuint UVBuffer;
		GLuint NormalBuffer;
		GLuint Texture;
		GLuint TextureID;

		vector<vec3> Verts;
		vector<vec3> Normals;
		vector<vec2> UVs;



		/////////////////////////////////////////
		// public getter
		int getID( void );
	};
}

#endif // DWI_MODEL
