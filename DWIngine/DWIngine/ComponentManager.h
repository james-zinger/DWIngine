#ifndef DWI_COMPONENTMANAGER
#define DWI_COMPONENTMANAGER

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

		/////////////////////////////////////////
		// ctor and dtor

		/**
		 * Constructor.
		 * @param [in,out]	Engine	If non-null, the engine.
		 */
		ComponentManager( DWIngine* Engine );

		/**
		 * Destructor.
		 */
		virtual ~ComponentManager( void );

		//////////////////////////////////////////
		// Event Methods

		/**
		 * Calls start on all objects in the component manager.
		 */
		virtual void Start( void ) = 0;

		/**
		 * Calls awake on all object in the component manager.
		 */
		virtual void Awake( void ) = 0;

		/**
		 * Calls update on all objects in the component manager.
		 */
		virtual void Update( void ) = 0;

		/**
		 * Calls fixed update on all object in the component manager
		 * @param	dt	The delta in time since last frame.
		 */
		virtual void FixedUpdate( float dt ) = 0;

		/**
		 * Calls late update on all object in the component manager.
		 */
		virtual void LateUpdate( void ) = 0;

	};
}

#endif // DWI_COMPONENTMANAGER
