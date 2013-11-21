#include "TransformManager.h"
#include "DWIngine.h"

namespace DWI
{
	/**
	 * @fn	TransformManager::TransformManager( DWIngine* Engine )
	 * @brief	Constructor.
	 * @param [in,out]	Engine	Must be non-null engine pointer.
	 */
	TransformManager::TransformManager( DWIngine* Engine ) : ComponentManager( Engine )
	{
		
	}

	/**
	 * @fn	TransformManager::~TransformManager()
	 * @brief	Destructor.
	 */
	TransformManager::~TransformManager( void )
	{
	}

	/**
	 * @fn	Transform* TransformManager::TransformFactory( GameObject* gameObject )
	 * @brief	Transform factory.
	 * @param [in,out]	gameObject	If non-null, the game object.
	 * @return	null if it fails, else a Transform*.
	 */
	Transform* TransformManager::TransformFactory( GameObject* gameObject )
	{
		Transform T = Transform( __keyToIndex.size(), gameObject );

		__transforms.push_back( T );

		__keyToIndex[ __keyToIndex.size() ] = __transforms.size() - 1;

		return &( __transforms.back() );
	}

	/**
	 * @fn	void TransformManager::Start( void )
	 * @brief	Calls Start on all transforms in the manager.
	 */
	void TransformManager::Start( void )
	{
		for ( vector<Transform>::iterator it = __transforms.begin(); it < __transforms.end(); it++ )
		{
			if ( it->__enabled )
			{
				it->Start();
			}
		}
	}

	/**
	 * @fn	void TransformManager::Update( void )
	 * @brief	Calls Update on all transforms in the manager.
	 */
	void TransformManager::Update( void )
	{
		for ( vector<Transform>::iterator it = __transforms.begin( ); it < __transforms.end( ); it++ )
		{
			if ( it->__enabled )
			{
				it->Update();
			}
		}
	}

	/**
	 * @fn	void TransformManager::FixedUpdate( float dt )
	 * @brief	Calls FixedUpdate on all transforms in the manager.
	 * @param	dt	The delta in time for every fixed update.
	 */
	void TransformManager::FixedUpdate( float dt )
	{
		for ( vector<Transform>::iterator it = __transforms.begin( ); it < __transforms.end( ); it++ )
		{
			if ( it->__enabled )
			{
				it->FixedUpdate( dt );
			}
		}
	}

	/**
	* @fn	void TransformManager::LateUpdate( void )
	* @brief	Calls LateUpdate on all transforms in the manager.
	*/
	void TransformManager::LateUpdate( void )
	{
		for ( vector<Transform>::iterator it = __transforms.begin( ); it < __transforms.end( ); it++ )
		{
			if ( it->__enabled )
			{
				it->LateUpdate();
			}
		}
	}
}