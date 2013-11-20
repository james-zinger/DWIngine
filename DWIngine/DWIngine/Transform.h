#ifndef DWI_TRANSFORM
#define DWI_TRANSFORM

#include "Component.h"
#include "DWMath.h"


namespace DWI
{
	///////////////////////////////////////////////////////////////////////////////////////////////
	class Transform : public Component
	{

		// The SceneManager manages all Transforms in the scene. Look to this class for functionality for
		// instantiation and destruction of Transforms and any other sensitive process.
		// friend class scene;
		friend class ComponentManager;

		/////////////////////////////////////////////////////////////////
	private:

		/////////////////////////////////////////////
		// Private member variables

		/////////////////////////////////////////////
		// ctor and dtor

		Transform( const unsigned int uniqueID );
		~Transform( void );


		/////////////////////////////////////////////////////////////////
	public:

		/////////////////////////////////////////////
		// public member variables
		Vector3			Position;
		Quaternion		Orientation;
		Vector3			Scale;
		Transform*		Parent;

		/////////////////////////////////////////////
		// public getters functions

		Vector3*		GetPosition( void );
		Quaternion*		GetOrientation( void );
		Vector3*		GetScale( void );

		/////////////////////////////////////////////
		// public setters functions
		void			SetPosition( Vector3* position );
		void			SetOrientation( Quaternion* quat );
		void			SetScale( Vector3* scale );
	};
}

#endif // DWI_TRANSFORM
