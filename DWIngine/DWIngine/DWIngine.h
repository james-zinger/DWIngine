#ifndef DWI_DWINGINE
#define DWI_DWINGINE

#include <string>

using std::string;



namespace DWI
{
	// Forward includes
	class AbstractRenderer;
	class App;
	class Input;
	class Log;
	class Resources;
	class Time;
	class Scene;
	class TransformManager;

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
		Input*				__input;
		bool				__isStopping;
		Log*				__log;
		AbstractRenderer*	__renderer;
		Resources*			__resources;
		Time*				__time;
		Scene*				__currentScene;
		TransformManager*	__transformManager;


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


#pragma region Event callbacks

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

#pragma endregion


		/////////////////////////////////////////////////////////////////
	public:


#pragma region Singleton methods

		/**
		 * @fn	static DWIngine* DWIngine::singleton( void );
		 * @brief	Returns a pointer to the singleton instance of the game engine. This cannot be called
		 * 			from DWIngine's constructor or any function called by its constructor.
		 * @return	The pointer to the DWIngine singleton instance.
		 */
		static DWIngine* singleton( void );

		/**
		 * @fn	static void DWIngine::destroySingleton( void );
		 * @brief	Destroys the DWIngine instance and releases it from heap memory.
		 */
		static void destroySingleton( void );

		/**
		 * @fn	static bool DWIngine::isSingletonNull( void );
		 * @brief	 Returns whether or not the singleton pointer is null.
		 * @return	true if singleton null, false if not.
		 */
		static bool isSingletonNull( void );

#pragma endregion

		/////////////////////////////////////////////
		// Start the engine

		/**
		 * @fn	void DWIngine::start( void );
		 * @brief	Initializes the game engine application and begins the render cycle.
		 */
		void start( void );
		void start( App* app );

		/**
		 * @fn	void DWIngine::stop( void );
		 * @brief	Causes the game loop to end after the next render cycle completes.
		 */
		void stop( void );


#pragma region Message logging

		/**
		 * @fn	void DWIngine::trace( const string& message );
		 * @brief	Trace out a message to the log file.
		 * @param	message	The message.
		 */
		void trace( const string& message );

		/**
		 * @fn	void DWIngine::logError( const string& message );
		 * @brief	Output an error message to the log file.
		 * @param	message	The message.
		 */
		void logError( const string& message );

		/**
		 * @fn	void DWIngine::logInfo( const string& message );
		 * @brief	Output an informational message to the log file.
		 * @param	message	The message.
		 */
		void logInfo( const string& message );

		/**
		 * @fn	void DWIngine::logWarning( const string& message );
		 * @brief	Output a warning message to the log file.
		 * @param	message	The message.
		 */
		void logWarning( const string& message );

#pragma endregion


#pragma region Timing

		/**
		 * @fn	double DWIngine::dt( void );
		 * @brief	Get the number of seconds since the scene was last rendered.
		 * @return	A double containing the number of seconds since the last render event.
		 */
		double dtSec( void );

		/**
		 * @fn	double DWIngine::dtMS( void );
		 * @brief	Get the number of milliseconds since the scene was last rendered.
		 * @return	A double containing the number of milliseconds since the last render event.
		 */
		double dtMS( void );

		/**
		 * @fn	double DWIngine::fps( void );
		 * @brief	Get the current frame rate at which rendering is occurring.
		 * @return	A double containing the current frame rate at which rendering is occurring.
		 */
		double fps( void );

		/**
		 * @fn	double DWIngine::time( void );
		 * @brief	Get the number of seconds that the app has been running for.
		 * @return	A double containing the number of seconds for which the app has been running.
		 */
		double timeSec( void );

		/**
		 * @fn	double DWIngine::timeMS( void );
		 * @brief	Get the number of milliseconds that the app has been running for.
		 * @return	A double containing the number of milliseconds for which the app has been running.
		 */
		double timeMS( void );

#pragma endregion


		/////////////////////////////////////////////
		// Getters for private members

		/**
		 * @fn	App* DWIngine::app( void );
		 * @brief	Returns a pointer to the app currently running in the game engine application.
		 * @return	A DWApp pointer to the app currently running in the game engine application.
		 */
		App* app( void );

		/**
		 * @fn	bool DWIngine::isStopping( void );
		 * @brief	Query if this object is stopping.
		 * @return	A boolean value of whther or not the application will quit after this render.
		 */
		bool isStopping( void );

		/**
		 * @fn	AbstractRenderer* DWIngine::renderer( void );
		 * @brief	Gets the renderer.
		 * @return	The AbstractRenderer used by the game engine application to render content.
		 */
		AbstractRenderer* renderer( void );

		/**
		 * @fn	Resources* DWIngine::resources( void );
		 * @brief	Get a pointer to the Resources used by the game engine application.
		 * @return	The Resources used by the game engine application to render content.
		 */
		Resources* resources( void );

		TransformManager* transformManager( void );

		/////////////////////////////////////////////
		// Setters for private members

		/**
		 * @fn	void DWIngine::app( App* value );
		 * @brief	Sets the current app running in the game engine application and hooks it to the engine.
		 * @param [in,out]	value	If non-null, the application.
		 */
		void app( App* value );
	};
}

#endif // DWI_DWINGINE
