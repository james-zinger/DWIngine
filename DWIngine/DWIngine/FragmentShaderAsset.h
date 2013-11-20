#ifndef DWI_FRAGMENTSHADERASSET
#define DWI_FRAGMENTSHADERASSET

#include "DWMath.h"
#include "AbstractAsset.h"
#include <string>

using std::string;




namespace DWI
{
	///////////////////////////////////////////////////////////////////////////////////////////////
	class FragmentShaderAsset : public AbstractAsset
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

		FragmentShaderAsset( string uniqueName, string fragmentShader );
		FragmentShaderAsset( string uniqueName );
		~FragmentShaderAsset( void );


		/////////////////////////////////////////
		// Getters

		string sourceCode( void );


		/////////////////////////////////////////
		// Setters

		void sourceCode( string value );

	};
}

#endif // DWI_FRAGEMENTSHADERASSET
