#ifndef DWI_GAMEOBJECT
#define DWI_GAMEOBJECT

#include <string>
#include "Transform.h";

using std::string;

namespace DWI
{
	///////////////////////////////////////////////////////////////////////////////////////////////
	class GameObject
	{

	/////////////////////////////////////////////////////////////
	private:

		GameObject( void );
		virtual ~GameObject( void );

		Transform* __transform;

		bool isEnabled;

	/////////////////////////////////////////////////////////////
	public:

		string name;
		
	};
}

#endif // DWI_GAMEOBJECT
