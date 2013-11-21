#ifndef DWI_VERTEXSHADERASSET
#define DWI_VERTEXSHADERASSET

#include "DWMath.h"
#include "AbstractAsset.h"
#include <string>

using std::string;




namespace DWI
{
	///////////////////////////////////////////////////////////////////////////////////////////////
	class VertexShaderAsset : public AbstractAsset
	{

	/////////////////////////////////////////////////////////////
	private:

		/////////////////////////////////////////
		// Private member variables

		string __sourceCode;



	/////////////////////////////////////////////////////////////
	public:

		/////////////////////////////////////////
		// ctor and dtor

		VertexShaderAsset( string uniqueName, string vertexShader );
		VertexShaderAsset( string uniqueName );
		~VertexShaderAsset( void );


		/////////////////////////////////////////
		// Getters

		string sourceCode( void );


		/////////////////////////////////////////
		// Setters

		void sourceCode( string value );

	};
}

#endif // DWI_VERTEXSHADERASSET
