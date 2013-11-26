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
	// Load file resources from the disk
	engine()->resources()->addVertexShaderFromFile( "StandardShading", "StandardShading.vertexshader" );
	engine()->resources()->addFragmentShaderFromFile( "StandardShading", "StandardShading.fragmentshader" );
	engine()->resources()->addTextureFromBmpFile( "Flag", "DOGE.bmp" );
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
	go->transform()->Translate( Vector3( -8, 5, 0 ) );

	// Create a cloth to operate on it
	int rows = 40;
	int cols = 64;
	float equilibrium = 0.25f;
	float nodeMass = 0.005f;
	float springCoeff = 20.0f;
	float dampingCoeff = 0.02f;
	__cloth.meshComponent( engine()->meshManager()->KeytoPointer( go->getMeshIndex() ) );
	__cloth.init( rows, cols, equilibrium, nodeMass, springCoeff, dampingCoeff );

	// Lock the leftmost columns of nodes in position (to the flag pole)
	std::vector<Node>& clothNodes = __cloth.nodes();
	for ( int row = 0; row < __cloth.rows(); row++ )
	{
		clothNodes[ row * __cloth.columns() ].locked = true;
	}
	//clothNodes[ 0 ].locked = true;
	//clothNodes[ clothNodes.size() - __cloth.columns() ].locked = true;

	// Position the camera in the scene
	DWI::Camera* cam = DWI::DWIngine::singleton()->camera();
	cam->setPosition( Vector3( 10, 0, 30 ) );

	engine()->trace( "Starting up..." );
}

void FlagApp::onPreRender( void )
{
	float dt = engine()->dtSec();
	if ( dt > 0.1f )
	{
		dt = 0.1f;
	}

	// Compute forces on the each node in the flag (wind and gravity)
	DWI::Vector3 flagForces( 
		 0, //5.0f * sinf( 0.2f * engine()->timeSec() ) + 0.0f, 
		 0, //-0.98f, 
		 0.0f
	);
	
	// Apply spring forces to the cloth nodes
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

	//engine()->trace( "PreRender" );
}

void FlagApp::onRender( void )
{
	//engine()->trace( "Render" );
}

void FlagApp::onPostRender( void )
{
	//__sstream.str( string() );
	//__sstream << "FPS: " << engine()->fps();
	//engine()->logInfo( __sstream.str() );

	//engine()->trace( "PostRender" );
}

void FlagApp::onStop( void )
{
	engine()->trace( "Shutting down..." );
}