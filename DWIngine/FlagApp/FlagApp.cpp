#include "DWIngine.h"
#include "Resources.h"
#include "FlagApp.h"
#include "GameObject.h"
#include "MeshManager.h"
#include "Scene.h"
#include "Camera.h"
#include "MeshAsset.h"
#include <sstream>

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
	__isStarting = true;
}

FlagApp::~FlagApp( void )
{
	// No resources to release
}


/////////////////////////////////////////////////////////////////
// Event callback overrides

void FlagApp::onStart( void )
{
	// Load our standard diffuse shader package
	engine()->resources()->addVertexShaderFromFile( "StandardShading", "StandardShading.vertexshader" );
	engine()->resources()->addFragmentShaderFromFile( "StandardShading", "StandardShading.fragmentshader" );

	//// GROUND ////

	// Build the ground resources
	engine()->resources()->addTextureFromBmpFile( "Ground", "Grass.bmp" );
	engine()->resources()->addMaterialFromString( "Ground", "StandardShading", "StandardShading", "Ground" );
	engine()->resources()->addMeshFromObjFile( "Ground", "Ground.obj", false );

	// Create the flag pole game object
	GameObject* go = GameObject::Instantiate(
		Vector3( 0, 0, 0 ),
		Quaternion(),
		Vector3( 10, 10, 10 ),
		engine()->currentScene()->GetRoot()->getTransformIndex()
	);
	go->addMesh( "Ground", "Ground" );

	///// FLAG POLE /////

	// Build the flag pole resources
	engine()->resources()->addTextureFromBmpFile( "FlagPole", "FlagPole.bmp" );
	engine()->resources()->addMaterialFromString( "FlagPole", "StandardShading", "StandardShading", "FlagPole" );
	engine()->resources()->addMeshFromObjFile( "FlagPole", "FlagPole.obj", false );

	// Create the flag pole game object
	go = GameObject::Instantiate(
		Vector3( 0, 15, 0 ),
		Quaternion(),
		Vector3( 3, 3, 3 ),
		engine()->currentScene()->GetRoot()->getTransformIndex()
	);
	go->addMesh( "FlagPole", "FlagPole" );

	///// FLAG CLOTH /////

	// Build the flag resources
	engine()->resources()->addTextureFromBmpFile( "Flag", "DOGE.bmp" );
	engine()->resources()->addMaterialFromString( "Flag", "StandardShading", "StandardShading", "Flag" );
	
	// Create a blank mesh asset for the flag to appear as cloth
	DWI::MeshAsset* meshAsset = new DWI::MeshAsset( "Flag", true );
	engine()->resources()->addMesh( "Flag", meshAsset );

	// Create the cloth game object
	go = GameObject::Instantiate(
		Vector3( 0, 30, 0 ),
		Quaternion(),
		Vector3( 1, 1, 1 ),
		engine()->currentScene()->GetRoot()->getTransformIndex()
	);
	go->addMesh( "Flag", "Flag" );

	// Create a cloth to operate on the flag
	int rows = 40;
	int cols = 64;
	float equilibrium = 0.25f;
	float maxDistance = 0.40f;
	float nodeMass = 0.005f;
	float springCoeff = 50.0f;
	float dampingCoeff = 0.02f;
	__cloth.meshComponent( engine()->meshManager()->KeytoPointer( go->getMeshIndex() ) );
	__cloth.init( rows, cols, equilibrium, maxDistance, nodeMass, springCoeff, dampingCoeff );

	// Lock the left-most columns of flag nodes in position (to the flag pole)
	std::vector<Node>& clothNodes = __cloth.nodes();
	for ( int row = 0; row < __cloth.rows(); row++ )
	{
		clothNodes[ row * __cloth.columns() ].locked = true;
	}

	// Position the camera in the scene
	DWI::Camera* cam = DWI::DWIngine::singleton()->camera();
	cam->setPosition( Vector3( 0, 5, 50 ) );
	cam->setLookAt( Vector3( 0, 15, 0 ) );

	engine()->trace( "Starting up..." );
}

void FlagApp::onPreRender( void )
{
	// Limit the time step to 1/10th of a second
	float dt = engine()->dtSec();
	if ( dt > 0.1f )
	{
		dt = 0.1f;
	}

	// Compute forces on the each node in the flag (wind and gravity)
	DWI::Vector3 flagForces(
		25.0f * sinf( 0.2f * engine()->timeSec() ), 
		-3.0f, 
		 0.0f
	);
	
	// Apply spring forces to random cloth nodes
	std::vector<Node>& clothNodes = __cloth.nodes();
	for ( int i = 0; i < clothNodes.size(); i++ )
	{
		float random = (float)rand() / (float)RAND_MAX;
		if ( random > 0.8f )
		{
			__cloth.applyForceToNode( i, flagForces );
		}
	}
	
	// Update the cloth
	__cloth.update( dt );
}

void FlagApp::onRender( void )
{
	
}

void FlagApp::onPostRender( void )
{
	// Report the FPS to track performance
	//__sstream.str( string() );
	//__sstream << "FPS: " << engine()->fps();
	//engine()->logInfo( __sstream.str() );
}

void FlagApp::onStop( void )
{
	engine()->trace( "Shutting down..." );
}