#ifndef DWI_APP
#define DWI_APP



namespace DWI
{

	// Forward includes
	class DWIngine;


	///////////////////////////////////////////////////////////////////////////////////////////////////
	class App
	{

	/////////////////////////////////////////////////////////////////
	private:

		/////////////////////////////////////////////
		// Private member variables

		DWIngine* __engine;



	/////////////////////////////////////////////////////////////////
	public:

		/////////////////////////////////////////////
		// ctor and dtor

		App( void );
		virtual ~App( void );


		/////////////////////////////////////////////
		// Getters

		/**
		* Return the engine to which this app is currently attached.
		*/
		DWIngine* engine( void );


		/////////////////////////////////////////////
		// Setters

		/**
		* Set the engine to which the app is currently attached.
		*/
		void engine( DWIngine* value );


		/////////////////////////////////////////////
		// Abstract event callbacks

		/**
		* This function is called by eventStart() when the game engine starts.
		*/
		virtual void onStart( void ) = 0;

		/**
		* This function is called by eventPreRender() when a pre-render stage occurs.
		*/
		virtual void onPreRender( void ) = 0;

		/**
		* This function is called by eventRender() when a render stage occurs.
		*/
		virtual void onRender( void ) = 0;

		/**
		* This function is called by eventPostRender() when a post-render stage occurs.
		*/
		virtual void onPostRender( void ) = 0;

		/**
		* This function is called by eventStop() when the game engine stops.
		*/
		virtual void onStop( void ) = 0;
	};
}

#endif // DWI_APP
