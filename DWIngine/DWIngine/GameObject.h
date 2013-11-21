#ifndef DWI_GAMEOBJECT
#define DWI_GAMEOBJECT

#include <string>
#include "Transform.h"

using std::string;

namespace DWI
{
	///////////////////////////////////////////////////////////////////////////////////////////////
	class GameObject
	{

	/////////////////////////////////////////////////////////////
	private:

		/**
		 * Default constructor.
		 */
		GameObject( void );

		/**
		 * Destructor.
		 */
		virtual ~GameObject( void );

		

		bool isEnabled;

	/////////////////////////////////////////////////////////////
	public:
		string name;

		static GameObject* Instantiate( Vector3& Position, Quaternion& Orientation, Vector3& Scale );
		
		Transform* transform;

	};
}

#endif // DWI_GAMEOBJECT
