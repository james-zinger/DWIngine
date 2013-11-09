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

		VertexShaderAsset( const string uniqueName, const string vertexShader );
		VertexShaderAsset( const string uniqueName );
		~VertexShaderAsset( void );


		/////////////////////////////////////////
		// Getters

		string sourceCode( void );


		/////////////////////////////////////////
		// Setters

		void sourceCode( const string value );

	};
}

#endif // DWI_VERTEXSHADERASSET
