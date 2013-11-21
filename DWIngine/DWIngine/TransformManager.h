#pragma once
#include <vector>
#include "ComponentManager.h"
#include "Transform.h"

using std::vector;

namespace DWI
{
	class DWIngine;
	class TransformManager : public ComponentManager
	{
	protected:
	
		/////////////////////////////////////
		// Protected member variables

		vector<Transform> __transform;

	public:

		/**
		 * Constructor.
		 * @param [in,out]	__engine	Must be non-null, the engine.
		 */
		TransformManager( DWIngine* __engine );

		/**
		 * Destructor.
		 */
		virtual ~TransformManager();

		/////////////////////////////////////
		// Event Method Overrides
		
		#pragma region Events

		/**
		 * Calls start on all transforms in the manager.
		 */
		virtual void Start( void );

		/**
		 * Calls awake on all transforms in the manager.
		 */
		virtual void Awake( void );

		/**
		 * Calls update on all transforms in the manager.
		 */
		virtual void Update( void );

		/**
		 * Calls fixed update on all transforms in the manager.
		 */
		virtual void FixedUpdate( float dt );

		/**
		 * Calls late update on all transforms in the manager.
		 */
		virtual void LateUpdate( void );
#pragma endregion
	};

}