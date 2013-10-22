#include "DWApp.h"
#include "HardwareClock.h"
#include "LogManager.h"
#include "DWIngine.h"
#include "OpenGL33Renderer.h"

#ifndef NULL
#define NULL 0
#endif



///////////////////////////////////////////////////////////////////////////////////////////////////
// Private

/////////////////////////////////////////////////////////////////
// Singleton variable

DWIngine* DWIngine::__singleton = NULL;


/////////////////////////////////////////////////////////////////
// ctor and dtor

DWIngine::DWIngine( void )
{
	__clock = HardwareClock::singleton();
	__logger = LogManager::singleton();
	__logger->outputLevel( LogLevel::ALL );
	__logger->filename( "DWIngine.log" );
	__isStopping = false;
	__renderer = new OpenGL33Renderer();
}

DWIngine::~DWIngine( void )
{
	delete __app;
	delete __renderer;
	LogManager::destroySingleton();
	HardwareClock::destroySingleton();

}


/////////////////////////////////////////////////////////////////
// Main game loop

void DWIngine::mainLoop( void )
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

void DWIngine::eventStart( void )
{
	// Perform end-user app behaviour
	__app->onStart();
}

void DWIngine::eventPreRender( void )
{
	// Perform end-user app behaviour
	__app->onPreRender();
}

void DWIngine::eventRender( void )
{
	// Refresh the game clock
	__clock->refresh( false );

	// Call render scene
	__renderer->RenderScene();

	// Perform end-user app behaviour
	__app->onRender();
}

void DWIngine::eventPostRender( void )
{
	// Perform end-user app behaviour
	__app->onPostRender();
}

void DWIngine::eventStop( void )
{
	// Perform end-user app behaviour
	__app->onStop();
}



///////////////////////////////////////////////////////////////////////////////////////////////////
// Public

/////////////////////////////////////////////////////////////////
// Singleton ctor and dtor

DWIngine* DWIngine::singleton( void )
{
	if ( __singleton == NULL )
	{
		__singleton = new DWIngine();
	}

	return __singleton;
}

void DWIngine::destroySingleton( void )
{
	if ( __singleton != NULL )
	{
		delete __singleton;
		__singleton = NULL;
	}
}


/////////////////////////////////////////////////////////////////
// Start and stop the engine

void DWIngine::start( DWApp* appToRun )
{
	// Link the app to this engine instance
	app( appToRun );

	// Begin the main event loop
	mainLoop();
}
void DWIngine::start( void )
{
	start( __app );
}

void DWIngine::stop( void )
{
	__isStopping = true;
}


/////////////////////////////////////////////////////////////////
// Message logging

void DWIngine::trace( const string& message )
{
	__logger->log( LogLevel::TRACE, message );
}

void DWIngine::logError( const string& message )
{
	__logger->log( LogLevel::ERROR, message );
}

void DWIngine::logInfo( const string& message )
{
	__logger->log( LogLevel::INFO, message );
}

void DWIngine::logWarning( const string& message )
{
	__logger->log( LogLevel::WARN, message );
}


/////////////////////////////////////////////////////////////////
// Timing

double DWIngine::dt( void )
{
	return __clock->dt();
}

double DWIngine::dtMS( void )
{
	return __clock->dtMS();
}

double DWIngine::fps( void )
{
	return 1.0 / dt();
}

double DWIngine::time( void )
{
	return __clock->currentAppTime();
}

double DWIngine::timeMS( void )
{
	return __clock->currentAppTimeMS();
}


/////////////////////////////////////////////////////////////////
// Getters for private members

DWApp* DWIngine::app( void )
{
	return __app;
}

bool DWIngine::isStopping( void )
{
	return __isStopping;
}


/////////////////////////////////////////////////////////////////
// Setters for private members

void DWIngine::app( DWApp* value )
{
	__app = value;
	__app->engine( this );
}