#include "DWIngine.h"
#include "TestApp.h"
#include "GameObject.h"
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

TestApp::TestApp( void )
{
	__numberOfRenders = 0;
	__maxNumberOfRenders = 100000;
}

TestApp::~TestApp( void )
{
	// No resources to release
}


/////////////////////////////////////////////////////////////////
// Event callback overrides

void TestApp::onStart( void )
{

	//engine()->trace( "Starting up..." );
	//vector<glm::vec3> verts = vector<glm::vec3>();
	//verts.assign(1,glm::vec3(0,0,0));
	//verts.push_back(glm::vec3(0.5,0,0));
	//verts.push_back(glm::vec3(0,0.5,0));
	//
	//vector<glm::vec3> normals = vector<glm::vec3>();
	//normals.push_back(glm::vec3(0,0,1));
	//normals.push_back(glm::vec3(0,0,1));
	//normals.push_back(glm::vec3(0,0,1));
	//
	//Primitive* p = new Primitive(PrimitiveType::Tri, 0,0,0, 0,0,1);

	DWI::GameObject* go = GameObject::Instantiate( Vector3( 0, 0, 0 ), Quaternion(), Vector3( 1, 1, 1 ) );
	
	Vector3* pos = go->transform->GetPosition();
	


	stringstream ss;
	ss.clear();
	ss << "The Position of GO: ( " << pos->x << ", " << pos->y << ", " << pos->z << " )\n";
	engine()->logInfo( ss.str() );

	engine()->trace( "Starting" );
}

void TestApp::onPreRender( void )
{
	//engine()->trace( "PreRender" );
}

void TestApp::onRender( void )
{
	if ( __numberOfRenders++ > __maxNumberOfRenders )
	{
		engine()->stop();
	}

	//__sstream.str( string() );
	//__sstream << "Render @ " << engine()->time() << " seconds  ::  Frame rate: " << engine()->fps() << "FPS";
	//engine()->trace( __sstream.str() );

	//engine()->trace( "Render" );
}

void TestApp::onPostRender( void )
{
	//engine()->trace( "PostRender" );
}

void TestApp::onStop( void )
{
	engine()->trace( "Shutting down..." );
}