#include "DWIngine.h"
#include "Resources.h"
#include "App.h"
#include "Time.h"
#include "Log.h"
#include "AbstractRenderer.h"
#include "OpenGL33Renderer.h"
#include "Input.h"

#ifndef NULL
#define NULL 0
#endif



///////////////////////////////////////////////////////////////////////////////////////////////////
// Private

/////////////////////////////////////////////////////////////////
// Singleton variable

DWI::DWIngine* DWI::DWIngine::__singleton = NULL;


/////////////////////////////////////////////////////////////////
// ctor and dtor

DWI::DWIngine::DWIngine( void )
{
	__isStopping = false;
	__log = Log::singleton();
	__log->filename( "DWI.log" );
	__log->outputLevel( LogLevel::DWI_ALL );
	__resources = Resources::singleton();
	__app = NULL;
	__renderer = new OpenGL33Renderer( this );
	__input = Input::singleton();
	__time = Time::singleton();
}

DWI::DWIngine::~DWIngine( void )
{
	// Destroy in reverse order
	Time::destroySingleton();
	Input::destroySingleton();
	delete __renderer;
	delete __app;
	Resources::destroySingleton();
	Log::destroySingleton();
}


/////////////////////////////////////////////////////////////////
// Main game loop

void DWI::DWIngine::mainLoop( void )
{
	// Begin the main event loop
	if ( __app != NULL )
	{
		// Run the startup process
		eventStart();

		while ( !__isStopping )
		{
			eventPreRender();
			eventRender();
			eventPostRender();
		}

		// Run the shutdown process
		eventStop();
	}
}


/////////////////////////////////////////////////////////////////
// Non-inheritable event callbacks

void DWI::DWIngine::eventStart( void )
{
	// Perform end-user app behaviour
	__app->onStart();
}

void DWI::DWIngine::eventPreRender( void )
{
	Input::singleton()->Update();
	// Perform end-user app behaviour
	__app->onPreRender();
}

void DWI::DWIngine::eventRender( void )
{
	// Refresh the game clock
	__time->refresh( false );

	// Call render scene
	__renderer->renderScene();

	// Perform end-user app behaviour
	__app->onRender();
}

void DWI::DWIngine::eventPostRender( void )
{

	// Perform end-user app behaviour
	__app->onPostRender();
}

void DWI::DWIngine::eventStop( void )
{
	// Perform end-user app behaviour
	__app->onStop();
}



///////////////////////////////////////////////////////////////////////////////////////////////////
// Public

/////////////////////////////////////////////////////////////////
// Singleton ctor and dtor

DWI::DWIngine* DWI::DWIngine::singleton( void )
{
	if ( __singleton == NULL )
	{
		__singleton = new DWIngine();
	}

	return __singleton;
}

void DWI::DWIngine::destroySingleton( void )
{
	if ( __singleton != NULL )
	{
		delete __singleton;
		__singleton = NULL;
	}
}


/////////////////////////////////////////////////////////////////
// Start and stop the engine

void DWI::DWIngine::start( App* appToRun )
{
	// Link the app to this engine instance
	app( appToRun );

	// Begin the main event loop
	mainLoop();
}
void DWI::DWIngine::start( void )
{
	start( __app );
}

void DWI::DWIngine::stop( void )
{
	__isStopping = true;
}


/////////////////////////////////////////////////////////////////
// Message logging

void DWI::DWIngine::trace( const string& message )
{
	__log->log( LogLevel::DWI_TRACE, message );
}

void DWI::DWIngine::logError( const string& message )
{
	__log->log( LogLevel::DWI_ERROR, message );
}

void DWI::DWIngine::logInfo( const string& message )
{
	__log->log( LogLevel::DWI_INFO, message );
}

void DWI::DWIngine::logWarning( const string& message )
{
	__log->log( LogLevel::DWI_WARN, message );
}


/////////////////////////////////////////////////////////////////
// Timing

double DWI::DWIngine::dtSec( void )
{
	return __time->dt();
}

double DWI::DWIngine::dtMS( void )
{
	return __time->dtMS();
}

double DWI::DWIngine::fps( void )
{
	return 1.0 / dtSec();
}

double DWI::DWIngine::timeSec( void )
{
	return __time->currentAppTime();
}

double DWI::DWIngine::timeMS( void )
{
	return __time->currentAppTimeMS();
}


/////////////////////////////////////////////////////////////////
// Getters

DWI::App* DWI::DWIngine::app( void )
{
	return __app;
}

bool DWI::DWIngine::isStopping( void )
{
	return __isStopping;
}

DWI::AbstractRenderer* DWI::DWIngine::renderer( void )
{
	return __renderer;
}

DWI::Resources* DWI::DWIngine::resources( void )
{
	return __resources;
}


/////////////////////////////////////////////////////////////////
// Setters

void DWI::DWIngine::app( DWI::App* value )
{
	__app = value;
	__app->engine( this );
}

////////////////////////////////////////////////////////////////
// Helper Methods

bool DWI::DWIngine::isSingletonNull( void )
{
	return __singleton == NULL;
}