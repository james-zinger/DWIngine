#ifndef DWI_GAMEOBJECT
#define DWI_GAMEOBJECT

#include <list>
#include <string>
#include "Transform.h"

using std::string;
using std::list;

namespace DWI
{
	///////////////////////////////////////////////////////////////////////////////////////////////
	class GameObject
	{

		friend class Scene;
	/////////////////////////////////////////////////////////////
	private:

		/**
		 * Default constructor.
		 */
		GameObject( void );

		

		static list<GameObject*>* __gameObjects;

		bool isEnabled;

	/////////////////////////////////////////////////////////////
	public:

		/**
		* Destructor.
		*/
		virtual ~GameObject( void );

		string name;

		static GameObject* Instantiate( Vector3& Position, Quaternion& Orientation, Vector3& Scale, int parent );
		
		int transform;

		static list<GameObject*>* GameObjectsList( void );

	};
}

#endif // DWI_GAMEOBJECT
