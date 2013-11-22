#ifndef DWI_COMPONENTMANAGER
#define DWI_COMPONENTMANAGER

#include <vector>
#include <unordered_map>
#include "Component.h"

using std::unordered_map;

namespace DWI
{

	class DWIngine;

	///////////////////////////////////////////////////////////////////////////////////////////////
	class ComponentManager
	{

		/////////////////////////////////////////////////////////////
	protected:

		/////////////////////////////////////////
		// Protected member variables

		DWIngine* __engine;
		unordered_map<int, int> __keyToIndex;

		/////////////////////////////////////////////////////////////
	public:

#pragma region		Constructor And Destructor

		/**
		 * @fn	ComponentManager::ComponentManager( DWIngine* Engine );
		 * @brief	Constructor.
		 * @param [in,out]	Engine	If non-null, the engine.
		 */
		ComponentManager( DWIngine* Engine );

		/**
		 * @fn	virtual ComponentManager::~ComponentManager( void );
		 * @brief	Destructor.
		 */
		virtual ~ComponentManager( void );

#pragma endregion


#pragma region Abstract Event Methods

		/**
		 * @fn	virtual void ComponentManager::Start( void ) = 0;
		 * @brief	Starts this object.
		 */
		virtual void Start( void ) = 0;

		/**
		 * @fn	virtual void ComponentManager::Update( void ) = 0;
		 * @brief	Calls update on all objects in the manager.
		 */
		virtual void Update( void ) = 0;

		/**
		 * @fn	virtual void ComponentManager::FixedUpdate( float dt ) = 0;
		 * @brief	Calls fixed update on all objects in the manager.
		 * @param	dt	The delta in time since last frame.
		 */
		virtual void FixedUpdate( float dt ) = 0;

		/**
		 * @fn	virtual void ComponentManager::LateUpdate( void ) = 0;
		 * @brief	Calls late update on all objects in the manager.
		 */
		virtual void LateUpdate( void ) = 0;

#pragma endregion

		virtual Component* KeytoPointer( int key ) = 0;
	};
}

#endif // DWI_COMPONENTMANAGER
