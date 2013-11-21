#include "Transform.h"

#ifndef NULL
#define NULL 0
#endif

namespace DWI
{

	///////////////////////////////////////////////////////////////////////////////////////////////////
	// Private

	/////////////////////////////////////////////////////////////////
	// ctor and dtor

	Transform::Transform( const unsigned int uniqueID, GameObject* gameObject ) : Component( uniqueID, gameObject )
	{
		Position = Vector3( 0.0f );
		Orientation = Quaternion();
		Scale = Vector3( 1.0f );
	}

	Transform::~Transform( void )
	{
		__enabled = false;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////
	// Public

	////////////////////////////////////////////////
	// Public Getter Functions

	Vector3* Transform::GetPosition( void )
	{
		return &Position;
	}

	Quaternion* Transform::GetOrientation( void )
	{
		return &Orientation;
	}

	Vector3* Transform::GetScale( void )
	{
		return &Scale;
	}

	////////////////////////////////////////////////
	// Public Setter Functions

	void Transform::SetPosition( Vector3* position )
	{
		Position = *position;
	}

	void Transform::SetOrientation( Quaternion* quat )
	{
		Orientation = *quat;
	}

	void Transform::SetScale( Vector3* scale )
	{
		Scale = *scale;
	}
}
