#ifndef DWI_MATERIALASSET
#define DWI_MATERIALASSET

#include "DWMath.h"
#include "AbstractAsset.h"
#include <string>
#include "GL\glew.h"

using std::string;

namespace DWI
{
	///////////////////////////////////////////////////////////////////////////////////////////////
	class MaterialAsset : public AbstractAsset
	{

	/////////////////////////////////////////////////////////////
	private:

		/////////////////////////////////////////
		// Private member variables

		string	__fragmentShaderUniqueName;
		string	__textureUniqueName;
		string	__vertexShaderUniqueName;

		GLuint __shaderProgramID;
		GLuint __shaderMatrixID;
		GLuint __shaderViewID;
		GLuint __shaderModelID;
		GLuint __shaderLightPos;
		GLuint __texture;
		GLuint __textureShaderID;

		bool __isShaderLoaded;
		bool __isTextureLoaded;

		/////////////////////////////////////////
		// Private GFX functions

		/**
		 * @brief	Loads shader to graphics card.
		 */
		void __loadShaderToGFXCard( void );

		/**
		 * @brief	Loads texture to graphics card.
		 */
		void __loadTextureToGFXCard( void );

		/**
		 * @brief	Unload shader from graphics card.
		 */
		void __unloadShaderFromGFXCard( void );

		/**
		 * @brief	Unload texture from graphics card.
		 */
		void __unloadTextureFromGFXCard( void );

	/////////////////////////////////////////////////////////////
	public:

		/////////////////////////////////////////
		// ctor and dtor

		MaterialAsset( string uniqueName, string fragmentShaderName, string vertexShaderName, string textureName );
		MaterialAsset( string uniqueName );
		~MaterialAsset( void );


		/////////////////////////////////////////
		// Getters

		/*
		* Returns the unique string used to look up the fragment shader program in the text data resources.
		*/
		string fragmentShaderUniqueName( void );

		/*
		* Returns the unique string used to look up the texture in the texture data resources.
		*/
		string textureUniqueName( void );

		/*
		* Returns the unique string used to look up the vertex shader program in the text data resources.
		*/
		string vertexShaderUniqueName( void );


		/////////////////////////////////////////
		// Setters

		/*
		* Sets the unique string used to look up the fragment shader program in the text data resources.
		*/
		void fragmentShaderUniqueName( string value );

		/*
		* Sets the unique string used to look up texture 1 in the texture data resources.
		*/
		void textureUniqueName( string value );

		/*
		* Sets the unique string used to look up the vertex shader program in the text data resources.
		*/
		void vertexShaderUniqueName( string value );

	};
}

#endif // DWI_MATERIALASSET
