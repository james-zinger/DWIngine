#include "GameObject.h"
#include "Transform.h"
#include "DWIngine.h"
#include "TransformManager.h"
#include "MeshManager.h"
#include "Scene.h"
#include "ObjectCouldNotBeCreatedException.h"
#include "Log.h"
#ifndef NULL
#define NULL 0
#endif



///////////////////////////////////////////////////////////////////////////////////////////////////
// Private

/////////////////////////////////////////////////////////////////
// ctor and dtor

namespace DWI
{
	list<GameObject*>* GameObject::__gameObjects = new list<GameObject*>();

	GameObject::GameObject( void )
	{
		__transform = DWIngine::singleton()->transformManager()->TransformFactory( this );
		__mesh = -1;
	}

	GameObject::~GameObject( void )
	{

	}

	int GameObject::getTransformIndex( void )
	{
		return __transform;
	}

	void GameObject::addMesh( string meshAsset, string matAsset )
	{
		__mesh = DWIngine::singleton()->meshManager()->MeshFactory( this, meshAsset, matAsset );
	}

	int GameObject::getMeshIndex( void )
	{
		return __mesh;
	}

	Transform* GameObject::transform( void )
	{
		return DWIngine::singleton()->transformManager()->KeytoPointer( __transform );
	}

	GameObject* GameObject::Instantiate( Vector3& Position, Quaternion& Orientation, Vector3& Scale, int parent )
	{
		
		if ( parent == -1 )
		{
			Log::LogError( "Transform Parent Cannot Be NULL" );
			throw ObjectCouldNotBeCreatedException( "Transform Parent cannot be NULL" );
		}
		GameObject* go = new GameObject();
		
		Transform* t = DWIngine::singleton()->transformManager()->KeytoPointer( go->__transform );

		t->Scale = Scale;
		t->Orientation = Orientation;
		t->Position = Position;
		t->SetParent(parent);

		__gameObjects->push_back( go );

		return go;
	}

	list<GameObject*>* GameObject::GameObjectsList( void )
	{
		return __gameObjects;
	}

}
