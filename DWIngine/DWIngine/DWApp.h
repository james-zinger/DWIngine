#ifndef DWAPP
#define DWAPP

// Forward include the engine
class DWIngine;



///////////////////////////////////////////////////////////////////////////////////////////////////
class DWApp
{

/////////////////////////////////////////////////////////////////
protected:

	/////////////////////////////////////////////
	// Private member variables

	DWIngine* __engine;



/////////////////////////////////////////////////////////////////
public:

	/////////////////////////////////////////////
	// ctor and dtor

	DWApp( void );
	virtual ~DWApp( void );


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

#endif // DWAPP