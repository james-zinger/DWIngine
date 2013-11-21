#include "MeshManager.h"
#include "DWIngine.h"

namespace DWI
{
	///////////////////////////////////////////////////////////////////////////////////////////////////
	// Private

	/////////////////////////////////////////////////////////////////
	// ctor and dtor

	MeshManager::MeshManager( DWIngine* Engine ) : ComponentManager( Engine )
	{

	}

	MeshManager::~MeshManager( void )
	{

	}

	Mesh* MeshManager::MeshFactory( GameObject* gameObject, MeshAsset* meshAsset, MaterialAsset* matAsset )
	{
		Mesh M = Mesh( __keyToIndex.size(), gameObject, meshAsset, matAsset );

		__meshes.push_back( M );

		__keyToIndex[ __keyToIndex.size() ] = __meshes.size() - 1;

		return &( __meshes.back() );
	}

	/**
	* @fn	void TransformManager::Start( void )
	* @brief	Calls Start on all transforms in the manager.
	*/
	void MeshManager::Start( void )
	{
		for ( vector<Mesh>::iterator it = __meshes.begin( ); it < __meshes.end( ); it++ )
		{
			if ( it->__enabled )
			{
				it->Start( );
			}
		}
	}

	/**
	* @fn	void TransformManager::Update( void )
	* @brief	Calls Update on all transforms in the manager.
	*/
	void MeshManager::Update( void )
	{
		for ( vector<Mesh>::iterator it = __meshes.begin( ); it < __meshes.end( ); it++ )
		{
			if ( it->__enabled )
			{
				it->Update( );
			}
		}
	}

	/**
	* @fn	void TransformManager::FixedUpdate( float dt )
	* @brief	Calls FixedUpdate on all transforms in the manager.
	* @param	dt	The delta in time for every fixed update.
	*/
	void MeshManager::FixedUpdate( float dt )
	{
		for ( vector<Mesh>::iterator it = __meshes.begin( ); it < __meshes.end( ); it++ )
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
	void MeshManager::LateUpdate( void )
	{
		for ( vector<Mesh>::iterator it = __meshes.begin( ); it < __meshes.end( ); it++ )
		{
			if ( it->__enabled )
			{
				it->LateUpdate( );
			}
		}
	}
}