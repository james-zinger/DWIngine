#include "Scene.h"
#include "DWIngine.h"
#include "TransformManager.h"

#ifndef NULL
#define NULL 0
#endif

namespace DWI
{

	///////////////////////////////////////////////////////////////////////////////////////////////////
	// Public

	/////////////////////////////////////////////////////////////////
	// ctor and dtor

	Scene::Scene( void )
	{

	}

	Scene::~Scene( void )
	{

	}

	void Scene::Start( void )
	{
		__rootObject = new GameObject();

		Transform* t = DWIngine::singleton()->transformManager()->KeytoPointer( __rootObject->transform );

		t->Position = Vector3( 0, 0, 0 );
		t->Orientation = Quaternion();
		t->Scale = Vector3( 1, 1, 1 );
		t->SetParent( -1 );
		GameObject::GameObjectsList()->push_back( __rootObject );
	}

	GameObject* Scene::GetRoot( void )
	{
		return __rootObject;
	}
}
