#ifndef DWI_DWINGINE
#define DWI_DWINGINE

#include <string>

using std::string;



namespace DWI
{
	// Forward includes
	class App;
	class HardwareClock;
	class Log;
	class AbstractRenderer;
	class OpenGL33Renderer;
	class Input;
	class Scene;
	class ComponentManager;
	///////////////////////////////////////////////////////////////////////////////////////////////////
	
	class DWIngine
	{

	/////////////////////////////////////////////////////////////////
	private:

		/////////////////////////////////////////////
		// Singleton variable

		static DWIngine* __singleton;


		/////////////////////////////////////////////
		// Private member variables

		App*				__app;
		HardwareClock*		__clock;
		bool				__isStopping;
		Log*				__logger;
		AbstractRenderer*	__renderer;
		Input*				__input;
		Scene*				__currentScene;
//		ComponentManager*	__componentManager;

		/////////////////////////////////////////////
		// ctor and dtor

		DWIngine( void );
		~DWIngine( void );


		/////////////////////////////////////////////
		// Main game loop

		/**
		 * The game loop happens in here. All event callbacks are called from this function, and when it
		 * ends the game is over.
		 */
		void mainLoop( void );


		/////////////////////////////////////////////
		// Event callbacks

		/**
		 * This function is called to start the game engine application.
		 */
		void eventStart( void );

		/**
		 * This function is called immediately before the scene is rendered.
		 */
		void eventPreRender( void );

		/**
		 * This function is called to render the scene.
		 */
		void eventRender( void );

		/**
		 * This function is called immediately after the scene is rendered.
		 */
		void eventPostRender( void );

		/**
		 * This function is called to end the game engine application.
		 */
		void eventStop( void );



	/////////////////////////////////////////////////////////////////
	public:

		/////////////////////////////////////////////
		// Singleton ctor and dtor

		/**
		 * Returns a pointer to the singleton instance of the game engine. This cannot be called from
		 * DWIngine's constructor or any function called by its constructor.
		 *
		 * @return	The pointer to the DWIngine singleton instance.
		 */		
		static DWIngine* singleton( void );

		/**
		 * Destroys the DWIngine instance and releases it from heap memory.
		 */
		static void destroySingleton( void );


		/////////////////////////////////////////////
		// Start the engine

		/**
		 * Initializes the game engine application and begins the render cycle.
		 */
		void start( void );
		void start( App* app );

		/**
		 * Causes the game loop to end after the next render cycle completes.
		 */
		void stop( void );


		/////////////////////////////////////////////
		// Message logging

		/**
		 * Trace out a message to the log file.
		 *
		 * @param	message	The message.
		 */
		void trace( const string& message );

		/**
		 * Output an error message to the log file.
		 *
		 * @param	message	The message.
		 */
		void logError( const string& message );

		/**
		 * Output an informational message to the log file.
		 *
		 * @param	message	The message.
		 */
		void logInfo( const string& message );

		/**
		 * Output a warning message to the log file.
		 *
		 * @param	message	The message.
		 */
		void logWarning( const string& message );


		/////////////////////////////////////////////
		// Timing

		/**
		 * Get the number of seconds since the scene was last rendered.
		 *
		 * @return	A double containing the number of seconds since the last render event.
		 */
		double dt( void );

		/**
		 * Get the number of milliseconds since the scene was last rendered.
		 *
		 * @return	A double containing the number of milliseconds since the last render event.
		 */
		double dtMS( void );

		/**
		 * Get the current frame rate at which rendering is occurring.
		 *
		 * @return	A double containing the current frame rate at which rendering is occurring.
		 */
		double fps( void );

		/**
		* Get the number of seconds that the app has been running for.
		* @returns A double containing the number of seconds for which the app has been running.
		*/
		double time( void );

		/**
		 * Get the number of milliseconds that the app has been running for.
		 *
		 * @return	A double containing the number of milliseconds for which the app has been running.
		 */
		double timeMS( void );


		/////////////////////////////////////////////
		// Getters for private members

		/**
		 * Returns a pointer to the app currently running in the game engine application.
		 *
		 * @return	A DWApp pointer to the app currently running in the game engine application.
		 */
		App* app( void );

		/**
		 * Returns whether or not the game engine application will stop after this render.
		 *
		 * @return	A boolean value of whther or not the application will quit after this render.
		 */
		bool isStopping( void );

		/**
		 * Get a pointer to the AbstractRenderer used by the game engine application.
		 *
		 * @return	The AbstractRenderer used by the game engine application to render content.
		 */
		AbstractRenderer* renderer( void );


		/////////////////////////////////////////////
		// Setters for private members

		/**
		 * Sets the current app running in the game engine application and hooks it to the engine.
		 *
		 * @param [in,out]	value	If non-null, the value.
		 */
		void app( App* value );

		////////////////////////////////////////////
		// Helper Methods

		/**
		 * Checks the engine singleton if it exists.
		 *
		 * @return	true if singleton null, false if not.
		 */
		static bool isSingletonNull( void );
	};
}

#endif // DWI_DWINGINE
