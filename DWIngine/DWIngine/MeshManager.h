#ifndef DWI_MESHMANAGER
#define DWI_MESHMANAGER

#include "ComponentManager.h"
#include "Mesh.h"

using std::vector;
using DWI::Mesh;

namespace DWI
{
	class DWIngine;
	///////////////////////////////////////////////////////////////////////////////////////////////
	class MeshManager : public ComponentManager
	{

	protected:

		vector<Mesh> __meshes;

		/////////////////////////////////////////////////////////
	private:

#pragma region		Constructor And Destructor

		/**
		 * @fn	MeshManager::MeshManager( DWIngine* Engine );
		 * @brief	Constructor.
		 * @param [in,out]	Engine	Must have a non null engine pointer.
		 */
		MeshManager( DWIngine* Engine );

		/**
		 * @fn	MeshManager::~MeshManager( void );
		 * @brief	Destructor.
		 */
		~MeshManager( void );

#pragma endregion

		/**
		 * @fn	Mesh* MeshManager::MeshFactory( GameObject* gameObject, MeshAsset* meshAsset,
		 * 		MaterialAsset* matAsset );
		 * @brief	Mesh factory method.
		 * @param [in,out]	gameObject	If non-null, the game object.
		 * @param [in,out]	meshAsset 	If non-null, the mesh asset.
		 * @param [in,out]	matAsset  	If non-null, the material asset.
		 * @return	null if it fails, else a Mesh*.
		 */
		Mesh* MeshFactory( GameObject* gameObject, MeshAsset* meshAsset, MaterialAsset* matAsset );

#pragma region Event Method Overrides

		/**
		* @fn	virtual void TransformManager::Start( void );
		* @brief	Calls Start on all meshes in the manager.
		*/
		virtual void Start( void );

		/**
		* @fn	virtual void TransformManager::Update( void );
		* @brief	Calls Update on all meshes in the manager.
		*/
		virtual void Update( void );

		/**
		* @fn	virtual void TransformManager::FixedUpdate( float dt );
		* @brief	Calls FixedUpdate on all meshes in the manager.
		* @param	dt	The delta in time for every fixed update.
		*/
		virtual void FixedUpdate( float dt );

		/**
		* @fn	virtual void TransformManager::LateUpdate( void );
		* @brief	Calls LateUpdate on all meshes in the manager.
		*/
		virtual void LateUpdate( void );

#pragma endregion

	};
}

#endif // DWI_MESHMANAGER
