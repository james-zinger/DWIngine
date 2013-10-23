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
	private:

		/////////////////////////////////////////////
		// Private member variables

		GameObject* __gameObject;
		const unsigned int __uniqueID;



	/////////////////////////////////////////////////////////////////
	public:

		/////////////////////////////////////////////
		// ctor and dtor

		Component( const unsigned int uniqueID );
		virtual ~Component( void );


		/////////////////////////////////////////////
		// Getters

		/**
		* Return the DWObject to which this component is attached.
		*/
		GameObject* gameObject( void );

		/**
		* Return the unique identifier of the component.
		*/
		unsigned int uniqueID( void );


		/////////////////////////////////////////////
		// Setters

		/**
		* Set the game object to which this component is attached.
		*/
		void gameObject( GameObject* value );
	};
}

#endif // DWI_COMPONENT
