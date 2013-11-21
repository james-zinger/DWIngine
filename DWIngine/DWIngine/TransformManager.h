#pragma once
#include <vector>
#include "ComponentManager.h"
#include "Transform.h"

using std::vector;

namespace DWI
{
	class DWIngine;

	/**
	 * @class	TransformManager
	 * @brief	Manager for transforms.
	 * @sa	ComponentManager
	 */
	class TransformManager : public ComponentManager
	{
	protected:

		/////////////////////////////////////
		// Protected member variables

		vector<Transform> __transforms;

	public:

#pragma region Constructor And Desctuctor

		/**
		 * @fn	TransformManager::TransformManager( DWIngine* __engine );
		 * @brief	Constructor.
		 * @param [in,out]	__engine	Must be non-null, the engine.
		 */
		TransformManager( DWIngine* __engine );

		/**
		 * @fn	virtual TransformManager::~TransformManager();
		 * @brief	Destructor.
		 */
		virtual ~TransformManager();

#pragma endregion

		/**
		 * @fn	Transform* TransformManager::TransformFactory( GameObject* gameObject );
		 * @brief	Transform factory.
		 * @param [in,out]	gameObject	The game object the transform is related to.
		 * @return	null if it fails, else a Transform*.
		 */
		Transform* TransformFactory( GameObject* gameObject );

#pragma region Event Method Overrides

		/**
		* @fn	virtual void TransformManager::Start( void );
		* @brief	Calls Start on all transforms in the manager.
		*/
		virtual void Start( void );

		/**
		* @fn	virtual void TransformManager::Update( void );
		* @brief	Calls Update on all transforms in the manager.
		*/
		virtual void Update( void );

		/**
		* @fn	virtual void TransformManager::FixedUpdate( float dt );
		* @brief	Calls FixedUpdate on all transforms in the manager.
		* @param	dt	The delta in time for every fixed update.
		*/
		virtual void FixedUpdate( float dt );

		/**
		* @fn	virtual void TransformManager::LateUpdate( void );
		* @brief	Calls LateUpdate on all transforms in the manager.
		*/
		virtual void LateUpdate( void );

#pragma endregion

	};

}