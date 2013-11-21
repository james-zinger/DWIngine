#include "Component.h"
#include "GameObject.h"

#ifndef NULL
#define NULL 0
#endif


namespace DWI
{
	///////////////////////////////////////////////////////////////////////////////////////////////////
	// Public

	/////////////////////////////////////////////////////////////////
	// ctor and dtor

	/**
	 * @fn	Component::Component( const unsigned int uniqueID, GameObject* gameObject )
	 * @brief	Constructor.
	 * @param	uniqueID			Unique identifier.
	 * @param [in,out]	gameObject	If non-null, the game object.
	 */
	Component::Component( const unsigned int uniqueID, GameObject* gameObject ) : __uniqueID( uniqueID )
	{
		__gameObject = gameObject;
		__enabled = true;
		Awake();
	}

	/**
	 * @fn	Component::~Component( void )
	 * @brief	Destructor.
	 */
	Component::~Component( void )
	{
		// Nothing to release
	}


	/////////////////////////////////////////////////////////////////
	// Getters

	GameObject* Component::gameObject( void )
	{
		return __gameObject;
	}

	unsigned int Component::uniqueID( void )
	{
		return __uniqueID;
	}

#pragma region Empty Virtual Events

	/**
	 * @fn	void Component::Start( void )
	 * @brief	Called on the object just before the first enable.
	 */
	void Component::Start( void )
	{

	}

	/**
	 * @fn	void Component::Awake( void )
	 * @brief	Called on the object when all objects are created.
	 */
	void Component::Awake( void )
	{

	}

	/**
	 * @fn	void Component::OnEnable( void )
	 * @brief	The OnEnable function on the object when the component is enabled.
	 */
	void Component::OnEnable( void )
	{

	}

	/**
	 * @fn	void Component::OnDisable( void )
	 * @brief	The OnDisable function on the object when the component is disabled.
	 */
	void Component::OnDisable( void )
	{

	}

	/**
	 * @fn	void Component::Update( void )
	 * @brief	The Update function on the component on every frame.
	 */
	void Component::Update( void )
	{

	}

	/**
	 * @fn	void Component::FixedUpdate( float dt )
	 * @brief	The Fixed Update function which should be called every fixed amount of time.
	 * @param	dt	The fixed amount of time between every fixed update.
	 */
	void Component::FixedUpdate( float dt )
	{

	}

	/**
	 * @fn	void Component::LateUpdate( void )
	 * @brief	The late update method which is called after update.
	 */
	void Component::LateUpdate( void )
	{

	}

#pragma endregion

}