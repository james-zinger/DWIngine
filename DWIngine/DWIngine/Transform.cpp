#include "Transform.h"
#include "DWIngine.h"
#include "TransformManager.h"
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
		__parent = -1;
	}

	Transform::~Transform( void )
	{
		__enabled = false;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////
	// Public
	
	void Transform::AddChild( int Child )
	{
		__children.push_back( Child );
	}

	bool Transform::RemoveChild( int Child )
	{
		Transform* child = DWIngine::singleton()->transformManager()->KeytoPointer( Child );

		for ( vector<int>::iterator it = __children.begin( ); it != __children.end( ); it++ )
		{
			int key = ( *it );

			Transform* T = DWIngine::singleton()->transformManager()->KeytoPointer( key );

			if ( T->uniqueID() == child->uniqueID() )
			{
				__children.erase( it );
				return true;
			}
		}
		return false;
	}

	
	
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

	int Transform::GetParent( void )
	{
		return __parent;
	}

	int Transform::GetNumberOfChildren( void )
	{
		return __children.size();
	}

	int Transform::GetChildIndexAtIndex( int index )
	{
		return __children[ index ];
	}

	void Transform::Rotate( Quaternion q )
	{
		Vector3 axis = glm::axis( q );
		float angle = glm::angle( q );
		Orientation = glm::rotate( Orientation, angle, axis );
	}

	void Transform::Translate( Vector3 t )
	{
		Position += t;
	}

	void Transform::Rotate( Vector3 axis, float angle )
	{
		Orientation = glm::rotate( Orientation, angle, axis );
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

	void Transform::SetParent( int parent )
	{
		if ( __parent != -1 )
		{
			Transform* T = DWIngine::singleton()->transformManager()->KeytoPointer( __parent );
			T->RemoveChild( this->uniqueID() );
		}
		
		__parent = parent;
		
		if ( parent != -1 )
		{
			Transform* T = DWIngine::singleton( )->transformManager( )->KeytoPointer( parent );
			T->AddChild( this->uniqueID() );
		}
	}
}
