#include "MaterialAsset.h"
#include "DWIngine.h"
#include "Resources.h"
#ifndef NULL
#define NULL 0
#endif

namespace DWI
{

	///////////////////////////////////////////////////////////////////////////////////////////////
	// Private
	
	void MaterialAsset::__loadShaderToGFXCard( void )
	{
		if ( !__isShaderLoaded )
		{
			GLuint VertexShaderID = glCreateShader( GL_VERTEX_SHADER );
			GLuint FragmentShaderID = glCreateShader( GL_FRAGMENT_SHADER );

			Resources* r = DWIngine::singleton()->resources();

			string fragSource = r->getFragmentShader( __fragmentShaderUniqueName )->sourceCode( );

			string vertexSource = r->getVertexShader( __vertexShaderUniqueName )->sourceCode();

			int Result = GL_FALSE;
			int InfoLogLength;

			char const* VertexSourcePointer = vertexSource.c_str();

			//Compile the Vertex Shader
			glShaderSource( VertexShaderID, 1, &VertexSourcePointer, NULL );
			glCompileShader( VertexShaderID );

			glGetShaderiv( VertexShaderID, GL_COMPILE_STATUS, &Result );
			glGetShaderiv( VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength );

			if ( InfoLogLength > 0 )
			{
				std::vector<char> VertexShaderErrorMessage( InfoLogLength + 1 );
				glGetShaderInfoLog( VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[ 0 ] );
				DWIngine::singleton()->logError( &VertexShaderErrorMessage[0] );
			}

			//Compile the Fragment Shader
			char const * FragmentSourcePointer = fragSource.c_str();
			glShaderSource( FragmentShaderID, 1, &FragmentSourcePointer, NULL );
			glCompileShader( FragmentShaderID );

			glGetShaderiv( FragmentShaderID, GL_COMPILE_STATUS, &Result );
			glGetShaderiv( FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength );

			if ( InfoLogLength > 0 )
			{
				std::vector<char> FragmentShaderErrorMessage( InfoLogLength + 1 );
				glGetShaderInfoLog( FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[ 0 ] );
				DWIngine::singleton( )->logError( &FragmentShaderErrorMessage[ 0 ] );
			}

			GLuint ProgramID = glCreateProgram();
			glAttachShader( ProgramID, VertexShaderID );
			glAttachShader( ProgramID, FragmentShaderID );
			glLinkProgram( ProgramID );

			glGetProgramiv( ProgramID, GL_LINK_STATUS, &Result );
			glGetProgramiv( ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength );
			if ( InfoLogLength > 0 )
			{
				std::vector<char> ProgramErrorMessage( InfoLogLength + 1 );
				glGetProgramInfoLog( ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[ 0 ] );
				DWIngine::singleton()->logError( &ProgramErrorMessage[ 0 ] );
			}

			glDeleteShader( VertexShaderID );
			glDeleteShader( FragmentShaderID );

			__shaderProgramID = ProgramID;

			__shaderMatrixID = glGetUniformLocation( ProgramID, "MVP" );
			__shaderViewID = glGetUniformLocation( ProgramID, "V" );
			__shaderModelID = glGetUniformLocation( ProgramID, "M" );
			__textureShaderID = glGetUniformLocation( ProgramID, "TextureSampler" );
			__shaderLightPos = glGetUniformLocation( ProgramID, "LightPosition_worldspace" );


			__isShaderLoaded = !__isShaderLoaded;
		}
	}

	void MaterialAsset::__loadTextureToGFXCard( void )
	{
		if ( !__isTextureLoaded )
		{
			Resources* r = DWIngine::singleton()->resources();

			TextureAsset* tex = r->getTexture( __textureUniqueName );

			

			GLuint textureID;
			glGenTextures( 1, &textureID );

			glBindTexture( GL_TEXTURE_2D, textureID );

			unsigned char * data = new unsigned char [tex->width() * tex->height() * 3];

			data = &tex->imageData()[ 0 ];

			glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, tex->width(), tex->height(), 0, GL_RGB, GL_UNSIGNED_BYTE, data );

			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
			glGenerateMipmap( GL_TEXTURE_2D );

			__texture = textureID;

			__isTextureLoaded = !__isTextureLoaded;
		}
	}

	void MaterialAsset::__unloadShaderFromGFXCard( void )
	{
		if ( __isShaderLoaded )
		{
			glDeleteProgram( __shaderProgramID );
		}
	}

	void MaterialAsset::__unloadTextureFromGFXCard( void )
	{
		if ( __isTextureLoaded )
		{
			glDeleteTextures( 1, &__texture );
		}
	}

	///////////////////////////////////////////////////////////////////////////////////////////////
	// Public

	/////////////////////////////////////////////////////////////
	// ctor and dtor

	MaterialAsset::MaterialAsset( string uniqueName, string fragmentShaderName, string vertexShaderName, string textureName ) : AbstractAsset( uniqueName )
	{
		__fragmentShaderUniqueName = fragmentShaderName;
		__textureUniqueName = textureName;
		__vertexShaderUniqueName = vertexShaderName;
		__isTextureLoaded = false;
		__isShaderLoaded = false;
		__loadShaderToGFXCard();
		__loadTextureToGFXCard();

	
	}

	MaterialAsset::MaterialAsset( string uniqueName ) : AbstractAsset( uniqueName )
	{
		__fragmentShaderUniqueName = "";
		__textureUniqueName = "";
		__vertexShaderUniqueName = "";

		__isTextureLoaded = false;
		__isShaderLoaded = false;
	}

	MaterialAsset::~MaterialAsset( void )
	{
		__unloadShaderFromGFXCard();
		__unloadTextureFromGFXCard();
	}


	/////////////////////////////////////////////////////////////
	// Getters

	string MaterialAsset::fragmentShaderUniqueName( void )
	{
		return __fragmentShaderUniqueName;
	}

	string MaterialAsset::textureUniqueName( void )
	{
		return __textureUniqueName;
	}

	string MaterialAsset::vertexShaderUniqueName( void )
	{
		return __vertexShaderUniqueName;
	}


	/////////////////////////////////////////////////////////////
	// Setters

	void MaterialAsset::fragmentShaderUniqueName( string value )
	{
		__fragmentShaderUniqueName = value;
	}

	void MaterialAsset::textureUniqueName( string value )
	{
		__textureUniqueName = value;
	}

	void MaterialAsset::vertexShaderUniqueName( string value )
	{
		__vertexShaderUniqueName = value;
	}
}