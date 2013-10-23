#ifndef DWI_MATERIAL
#define DWI_MATERIAL

#include "DWMath.h"
#include "DWResource.h"
#include <string>

using std::string;



namespace DWI
{
	///////////////////////////////////////////////////////////////////////////////////////////////
	class Material : public DWResource
	{

	/////////////////////////////////////////////////////////////
	private:

		/////////////////////////////////////////
		// Private member variables

		string	__fragmentShaderUniqueName;
		Vector4	__texture1BlendColour;
		string	__texture1UniqueName;
		Vector4	__texture2BlendColour;
		string	__texture2UniqueName;
		string	__vertexShaderUniqueName;



	/////////////////////////////////////////////////////////////
	public:

		/////////////////////////////////////////
		// ctor and dtor

		Material( const string uniqueName );
		~Material( void );


		/////////////////////////////////////////
		// Getters

		/*
		* Returns the unique string used to look up the fragment shader program in the text data resources.
		*/
		string& fragmentShaderUniqueName( void );

		/*
		* Returns an RGBA-formatted colour to use for texture 1 when texture blending.
		*/
		Vector4& texture1BlendColour( void );

		/*
		* Returns the unique string used to look up texture 1 in the texture data resources.
		*/
		string& texture1UniqueName( void );

		/*
		* Returns an RGBA-formatted colour to use for texture 2 when texture blending.
		*/
		Vector4& texture2BlendColour( void );

		/*
		* Returns the unique string used to look up texture 2 in the texture data resources.
		*/
		string& texture2UniqueName( void );

		/*
		* Returns the unique string used to look up the vertex shader program in the text data resources.
		*/
		string& vertexShaderUniqueName( void );


		/////////////////////////////////////////
		// Setters

		/*
		* Sets the unique string used to look up the fragment shader program in the text data resources.
		*/
		void fragmentShaderUniqueName( const string& value );

		/*
		* Sets the RGBA-formatted colour to use for texture 1 when texture blending.
		*/
		void texture1BlendColour( const Vector4& value );

		/*
		* Sets the unique string used to look up texture 1 in the texture data resources.
		*/
		void texture1UniqueName( const string& value );

		/*
		* Sets the RGBA-formatted colour to use for texture 2 when texture blending.
		*/
		void texture2BlendColour( const Vector4& value );

		/*
		* Sets the unique string used to look up texture 2 in the texture data resources.
		*/
		void texture2UniqueName( const string& value );

		/*
		* Sets the unique string used to look up the vertex shader program in the text data resources.
		*/
		void vertexShaderUniqueName( const string& value );

	};
}

#endif // DWI_MATERIAL
