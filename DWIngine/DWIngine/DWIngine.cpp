#include "DWIngine.h"
#include "App.h"
#include "HardwareClock.h"
#include "Log.h"
#include "OpenGL33Renderer.h"

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
	__app = NULL;
	__clock = HardwareClock::singleton();
	__logger = Log::singleton();
	__logger->outputLevel( LogLevel::DWI_ALL );
	__logger->filename( "DWI.log" );
	__isStopping = false;
	__renderer = new OpenGL33Renderer( this );
}

DWI::DWIngine::~DWIngine( void )
{
	delete __app;
	delete __renderer;
	Log::destroySingleton();
	HardwareClock::destroySingleton();

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
	// Perform end-user app behaviour
	__app->onPreRender();
}

void DWI::DWIngine::eventRender( void )
{
	// Refresh the game clock
	__clock->refresh( false );

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
	__logger->log( LogLevel::DWI_TRACE, message );
}

void DWI::DWIngine::logError( const string& message )
{
	__logger->log( LogLevel::DWI_ERROR, message );
}

void DWI::DWIngine::logInfo( const string& message )
{
	__logger->log( LogLevel::DWI_INFO, message );
}

void DWI::DWIngine::logWarning( const string& message )
{
	__logger->log( LogLevel::DWI_WARN, message );
}


/////////////////////////////////////////////////////////////////
// Timing

double DWI::DWIngine::dt( void )
{
	return __clock->dt();
}

double DWI::DWIngine::dtMS( void )
{
	return __clock->dtMS();
}

double DWI::DWIngine::fps( void )
{
	return 1.0 / dt();
}

double DWI::DWIngine::time( void )
{
	return __clock->currentAppTime();
}

double DWI::DWIngine::timeMS( void )
{
	return __clock->currentAppTimeMS();
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


/////////////////////////////////////////////////////////////////
// Setters

void DWI::DWIngine::app( DWI::App* value )
{
	__app = value;
	__app->engine( this );
}