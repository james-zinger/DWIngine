#ifndef DWI_COMPONENTMANAGER
#define DWI_COMPONENTMANAGER

#include <unordered_map>
#include <vector>
#include "Component.h"

using std::vector;
using std::unordered_map;

namespace DWI
{
	///////////////////////////////////////////////////////////////////////////////////////////////
	class ComponentManager
	{

	/////////////////////////////////////////////////////////////
	protected:

		/////////////////////////////////////////
		// Protected member variables

		vector<Component>			__components;
		unordered_map<int, int>		__idsToIndexMap;

	/////////////////////////////////////////////////////////////
	public:

		/////////////////////////////////////////
		// ctor and dtor

		ComponentManager( void );
		virtual ~ComponentManager( void );



	};
}

#endif // DWI_COMPONENTMANAGER
