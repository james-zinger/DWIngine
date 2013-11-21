#include "GameObject.h"
#include "Transform.h"
#include "DWIngine.h"
#include "TransformManager.h"
#ifndef NULL
#define NULL 0
#endif



///////////////////////////////////////////////////////////////////////////////////////////////////
// Private

/////////////////////////////////////////////////////////////////
// ctor and dtor

namespace DWI
{
	GameObject::GameObject( void )
	{
		transform = DWIngine::singleton()->transformManager()->TransformFactory( this );
	}

	GameObject::~GameObject( void )
	{

	}

	GameObject* GameObject::Instantiate( Vector3& Position, Quaternion& Orientation, Vector3& Scale )
	{
		GameObject* go = new GameObject();
		
		go->transform->Scale = Scale;
		go->transform->Orientation = Orientation;
		go->transform->Position = Position;

		return go;
	}
}
