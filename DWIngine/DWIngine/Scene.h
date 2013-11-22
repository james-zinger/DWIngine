#ifndef DWI_SCENE
#define DWI_SCENE
#include "GameObject.h"
namespace DWI
{
	///////////////////////////////////////////////////////////////////////////////////////////////////
	class Scene
	{

		
		///////////////////////////////////////////////////
	private:
		///////////////////////////////
		// Private Member Variables
		
		GameObject* __rootObject;

		///////////////////////////////////////////////////
	public:

		/////////////////////////////////////////
		// ctor and dtor

		Scene( void );
		~Scene( void );

		/**
		 * @fn	void Scene::Start( void );
		 * @brief	Starts this object.
		 */
		void Start( void );

		/**
		 * @fn	GameObject* Scene::GetRoot( void );
		 * @brief	Gets the root GameObject.
		 * @return	null if it fails, else the root.
		 */
		GameObject* GetRoot( void );

	};
}

#endif // DWI_SCENE
