#ifndef DWI_MESHASSET
#define DWI_MESHASSET

#include "DWMath.h"
#include "AbstractAsset.h"
#include <string>
#include <vector>

using std::string;
using std::vector;




namespace DWI
{
	///////////////////////////////////////////////////////////////////////////////////////////////
	class MeshAsset : public AbstractAsset
	{

	/////////////////////////////////////////////////////////////
	private:

		/////////////////////////////////////////
		// Private member variables

		vector<Vector3> __normals;
		vector<Vector2> __uvs;
		vector<Vector3> __vertices;



	/////////////////////////////////////////////////////////////
	public:

		/////////////////////////////////////////
		// ctor and dtor
		
		MeshAsset( const string uniqueName );
		~MeshAsset( void );


		/////////////////////////////////////////
		// Getters

		vector<Vector3>& normals( void );
		vector<Vector2>& uvs( void );
		vector<Vector3>& vertices( void );

	};
}

#endif // DWI_MESHASSET
