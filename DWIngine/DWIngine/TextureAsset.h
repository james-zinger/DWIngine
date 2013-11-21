#ifndef DWI_TEXTUREASSET
#define DWI_TEXTUREASSET

#include "DWMath.h"
#include "AbstractAsset.h"
#include <string>
#include <vector>

using std::string;
using std::vector;




namespace DWI
{
	///////////////////////////////////////////////////////////////////////////////////////////////
	class TextureAsset : public AbstractAsset
	{

	/////////////////////////////////////////////////////////////
	private:

		/////////////////////////////////////////
		// Private member variables

		int						__height;
		vector<unsigned char>	__imageData;
		int						__width;



	/////////////////////////////////////////////////////////////
	public:

		/////////////////////////////////////////
		// ctor and dtor

		TextureAsset( string uniqueName );
		~TextureAsset( void );


		/////////////////////////////////////////
		// Getters

		int height( void );
		vector<unsigned char>& imageData( void );
		int width( void );


		/////////////////////////////////////////
		// Setters

		void height( int value );
		void width( int value );

	};
}

#endif // DWI_TEXTUREASSET
