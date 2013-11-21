#ifndef DWI_COMPONENT
#define DWI_COMPONENT



namespace DWI
{

	// Forward includes
	class GameObject;


	///////////////////////////////////////////////////////////////////////////////////////////////
	class Component
	{

	/////////////////////////////////////////////////////////////////
	protected:

#pragma region Private Member variables

		/**
		 * @brief	The pointer to the parent gameobject.
		 */		
		GameObject* __gameObject;

		/**
		 * @brief	Unique identifier.
		 */
		const unsigned int __uniqueID;

		/**
		 * @brief	true to enable, false to disable.
		 */
		bool __enabled;

#pragma endregion

		/**
		 * @fn	Component::Component( const unsigned int uniqueID, GameObject* gameObject );
		 * @brief	Constructor.
		 * @param	uniqueID			Unique identifier.
		 * @param [in,out]	gameObject	.
		 */
		Component( const unsigned int uniqueID, GameObject* gameObject );

		

	/////////////////////////////////////////////////////////////////
	public:




		/**
		 * @fn	virtual Component::~Component( void );
		 * @brief	Destructor.
		 */
		virtual ~Component( void );

		/////////////////////////////////////////////
		// Getters

		/**
		 * @fn	GameObject* Component::gameObject( void );
		 * @brief	Game object.
		 * @return	null if it fails, else a GameObject*.
		 */
		GameObject* gameObject( void );

		/**
		 * @fn	bool Component::isEnabled( void );
		 * @brief	Query if this object is enabled.
		 * @return	true if enabled, false if not.
		 */
		bool isEnabled( void );


		/**
		 * @fn	unsigned int Component::uniqueID( void );
		 * @brief	Unique identifier.
		 * @return	The unique identifier of the componet
		 */
		unsigned int uniqueID( void );

		/////////////////////////////////////////////
		// Setters

		/**
		 * @fn	void Component::setEnabled( bool enabled );
		 * @brief	Sets an enabled.
		 * @param	enabled	true to enable, false to disable.
		 */		
		void setEnabled( bool enabled );

#pragma region Events

		/**
		 * @fn	virtual void Component::Start( void );
		 * @brief	Called on the object just before the first enable.
		 */
		virtual void Start( void );

		/**
		 * @fn	virtual void Component::Awake( void );
		 * @brief	Called on the object when all objects are created.
		 */
		virtual void Awake( void );

		/**
		 * @fn	virtual void Component::OnEnable( void );
		 * @brief	The OnEnable function on the object when the component is enabled.
		 */
		virtual void OnEnable( void );

		/**
		 * @fn	virtual void Component::OnDisable( void );
		 * @brief	The OnDisable function on the object when the component is disabled.
		 */
		virtual void OnDisable( void );

		/**
		 * @fn	virtual void Component::Update( void );
		 * @brief	The Update function on the component on every frame
		 */
		virtual void Update( void );

		/**
		 * @fn	virtual void Component::FixedUpdate( float dt );
		 * @brief	The Fixed Update function which should be called every fixed amount of time.
		 * @param	dt	The fixed amount of time between every fixed update.
		 */
		virtual void FixedUpdate( float dt );

		/**
		 * @fn	virtual void Component::LateUpdate( void );
		 * @brief	The late update method which is called after update.
		 */
		virtual void LateUpdate( void );

#pragma endregion

	};
}

#endif // DWI_COMPONENT
