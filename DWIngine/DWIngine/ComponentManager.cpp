#include "ComponentManager.h"
#include "DWIngine.h"
#include "ObjectCouldNotBeCreatedException.h"

///////////////////////////////////////////////////////////////////////////////////////////////
// Public

namespace DWI
{
	/**
	 * @fn	ComponentManager::ComponentManager( DWIngine* Engine )
	 * @brief	Constructor.
	 * @exception	ObjectCouldNotBeCreatedException	Thrown when an Object Could Not Be Created
	 * 													error condition occurs.
	 * @param [in,out]	Engine	Must be non-null engine pointer.
	 */
	ComponentManager::ComponentManager( DWIngine* Engine )
	{
		if ( Engine == NULL )
			throw ObjectCouldNotBeCreatedException( "Component manager could not be created. Engine* is NULL" );

		__engine = Engine;
	}

	/**
	 * @fn	ComponentManager::~ComponentManager( void )
	 * @brief	Destructor.
	 */
	ComponentManager::~ComponentManager( void )
	{
		__engine = NULL;
	}

}