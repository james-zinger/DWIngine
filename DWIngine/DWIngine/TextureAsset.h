#ifndef DWI_TEXTUREASSET
#define DWI_TEXTUREASSET

#include "DWMath.h"
#include "AbstractAsset.h"
#include <string>

using std::string;




namespace DWI
{
	///////////////////////////////////////////////////////////////////////////////////////////////
	class TextureAsset : public AbstractAsset
	{

	/////////////////////////////////////////////////////////////
	private:

		/////////////////////////////////////////
		// Private member variables

		unsigned char* __imageData;



	/////////////////////////////////////////////////////////////
	public:

		/////////////////////////////////////////
		// ctor and dtor

		TextureAsset( const string uniqueName, unsigned char* data );
		TextureAsset( const string uniqueName );
		~TextureAsset( void );


		/////////////////////////////////////////
		// Getters

		unsigned char* imageData( void );


		/////////////////////////////////////////
		// Setters

		void imageData( unsigned char* value );

	};
}

#endif // DWI_TEXTUREASSET
