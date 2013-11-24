#include "DWIngine.h"
#include "Resources.h"
#include "FlagApp.h"
#include "GameObject.h"
#include "MeshManager.h"
#include "Scene.h"
#include "Camera.h"
#include "MeshAsset.h"
#include <sstream>
//#include "Primitive.h"

#ifndef NULL
#define NULL 0
#endif

using DWI::Vector3;
using DWI::Quaternion;
using DWI::GameObject;
///////////////////////////////////////////////////////////////////////////////////////////////////
// Public 

/////////////////////////////////////////////////////////////////
// ctor and dtor

FlagApp::FlagApp( void )
{

}

FlagApp::~FlagApp( void )
{
	// No resources to release
}


/////////////////////////////////////////////////////////////////
// Event callback overrides

void FlagApp::onStart( void )
{
	// Load file resources from the disk
	engine()->resources()->addVertexShaderFromFile( "StandardShading", "StandardShading.vertexshader" );
	engine()->resources()->addFragmentShaderFromFile( "StandardShading", "StandardShading.fragmentshader" );
	engine()->resources()->addTextureFromBmpFile( "Flag", "m16.bmp" );
	engine()->resources()->addMaterialFromString( "Flag", "StandardShading", "StandardShading", "Flag" );
	
	// Create a blank mesh asset for the cloth to use
	DWI::MeshAsset* meshAsset = new DWI::MeshAsset( "Flag", true );
	engine()->resources()->addMesh( "Flag", meshAsset );

	// Create the cloth game object
	GameObject* go = GameObject::Instantiate(
		Vector3( 0, 0, 0 ),
		Quaternion(),
		Vector3( 1, 1, 1 ),
		engine()->currentScene()->GetRoot()->getTransformIndex()
	);
	go->addMesh( "Flag", "Flag" );
	//go->transform()->Scale = Vector3( 0.5f, 0.5f, 0.5f );
	//go->transform()->Rotate( Vector3( 0, 1, 0 ), 45 );
	//go->transform()->Translate( Vector3( 1, 1, 0 ) );

	// Create a cloth to operate on it
	int rows = 10;
	int cols = 16;
	float equilibrium = 1.0f;
	float nodeMass = 1.0f;
	float springCoeff = 1.0f;
	float dampingCoeff = 1.0f;
	__cloth.meshComponent( engine()->meshManager()->KeytoPointer( go->getMeshIndex() ) );
	__cloth.init( rows, cols, equilibrium, nodeMass, springCoeff, dampingCoeff );

	// Position the camera in the scene
	DWI::Camera* cam = DWI::DWIngine::singleton()->camera();
	cam->setPosition( Vector3( -10, 10, -10 ) );



	engine()->trace( "Starting up..." );
}

void FlagApp::onPreRender( void )
{
	// Update the cloth
	//__cloth.update( engine()->dtSec() );

	//engine()->trace( "PreRender" );
}

void FlagApp::onRender( void )
{
	//engine()->trace( "Render" );
}

void FlagApp::onPostRender( void )
{
	//engine()->trace( "PostRender" );
}

void FlagApp::onStop( void )
{
	engine()->trace( "Shutting down..." );
}