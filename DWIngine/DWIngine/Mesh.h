#ifndef DWI_MESH
#define DWI_MESH

#include "Component.h"
#include "DWMath.h"

namespace DWI
{
	///////////////////////////////////////////////////////////////////////////////////////////////
	class Mesh : public Component
	{
		friend class MeshManager;
	/////////////////////////////////////////////////////////////
	private:

		/////////////////////////////////////////
		// ctor and dtor

		Mesh( const unsigned int uniqueID, GameObject* gameObject );

	public:
		virtual ~Mesh( void );

	};
}

#endif // DWI_MESH
