#ifndef DWI_MATERIALASSET
#define DWI_MATERIALASSET

#include "DWMath.h"
#include "AbstractAsset.h"
#include <string>

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
