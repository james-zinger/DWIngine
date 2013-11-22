#include "DWIngine.h"
#include "Resources.h"
#include "App.h"
#include "Time.h"
#include "Log.h"
#include "AbstractRenderer.h"
#include "OpenGL33Renderer.h"
#include "Input.h"
#include "Scene.h"
#include "TransformManager.h"
#include "GameObject.h"
#ifndef NULL
#define NULL 0
#endif


namespace DWI
{
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
		__time = Time::singleton( );
		__log = Log::singleton();
		__log->outputLevel( LogLevel::DWI_ALL );
		__isStopping = false;
		__renderer = new OpenGL33Renderer( this );
		__input = Input::singleton();
		__currentScene = new Scene();
		__transformManager = new TransformManager( this );
		__resources = Resources::singleton();
	}
	
	DWI::DWIngine::~DWIngine( void )
	{
		delete __app;
		delete __renderer;
		delete __currentScene;
		delete __transformManager;
		Log::destroySingleton();
		Time::destroySingleton();
		Input::destroySingleton();
		Resources::destroySingleton();

		list<GameObject*>::iterator it;
		for ( it = GameObject::GameObjectsList( )->begin( ); it != GameObject::GameObjectsList()->end( ); it++ )
		{
			delete ( *it );
		}

		delete (GameObject::GameObjectsList());
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

	void DWIngine::eventStart( void )
	{
		__currentScene->Start();
		// Perform end-user app behaviour
		__app->onStart();
	}

	void DWIngine::eventPreRender( void )
	{
		Input::singleton()->Update();
		
		__transformManager->Update();
		__transformManager->LateUpdate();
		// Perform end-user app behaviour
		__app->onPreRender();
	}

	void DWIngine::eventRender( void )
	{
		// Refresh the game clock
		__time->refresh( false );

		// Call render scene
		__renderer->renderScene();

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

	bool DWI::DWIngine::isSingletonNull( void )
	{
		return __singleton == NULL;
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
		return __time->dt( );
	}

	double DWI::DWIngine::dtMS( void )
	{
		return __time->dtMS( );
	}

	double DWI::DWIngine::fps( void )
	{
		return 1.0 / dtSec();
	}

	double DWI::DWIngine::timeSec( void )
	{
		return __time->currentAppTime( );
	}

	double DWI::DWIngine::timeMS( void )
	{
		return __time->currentAppTimeMS( );
	}


	/////////////////////////////////////////////////////////////////
	// Getters

	DWI::App* DWIngine::app( void )
	{
		return __app;
	}

	bool DWIngine::isStopping( void )
	{
		return __isStopping;
	}

	AbstractRenderer* DWIngine::renderer( void )
	{
		return __renderer;
	}

	Resources* DWIngine::resources( void )
	{
		return __resources;
	}

	TransformManager* DWIngine::transformManager( void )
	{
		return __transformManager;
	}

	Scene* DWIngine::currentScene( void )
	{
		return __currentScene;
	}

	/////////////////////////////////////////////////////////////////
	// Setters

	void DWI::DWIngine::app( DWI::App* value )
	{
		__app = value;
		__app->engine( this );
	}

}