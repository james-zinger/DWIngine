#include "DWIngine.h"
#include "Resources.h"
#include "TestApp.h"
//#include "Primitive.h"

#ifndef NULL
#define NULL 0
#endif



///////////////////////////////////////////////////////////////////////////////////////////////////
// Public 

/////////////////////////////////////////////////////////////////
// ctor and dtor

TestApp::TestApp( void )
{
	__numberOfRenders = 0;
	__maxNumberOfRenders = 10000;
}

TestApp::~TestApp( void )
{
	// No resources to release
}


/////////////////////////////////////////////////////////////////
// Event callback overrides

void TestApp::onStart( void )
{
	// Try to load an .OBJ file as a test
	engine()->resources()->addMeshFromObjFile( "M-16", "M16_model.obj" );

	engine()->trace( "Starting up..." );
}

void TestApp::onPreRender( void )
{
	engine()->trace( "PreRender" );
}

void TestApp::onRender( void )
{
	if ( __numberOfRenders++ > __maxNumberOfRenders )
	{
		engine()->stop();
	}

	__sstream.str( string() );
	__sstream << "Render @ " << engine()->timeSec() << " seconds  ::  Frame rate: " << engine()->fps() << "FPS";
	engine()->trace( __sstream.str() );

	engine()->trace( "Render" );
}

void TestApp::onPostRender( void )
{
	engine()->trace( "PostRender" );
}

void TestApp::onStop( void )
{
	engine()->trace( "Shutting down..." );
}