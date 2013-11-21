#ifndef TESTAPP
#define TESTAPP

#include <sstream>
#include "App.h"

using namespace std;



///////////////////////////////////////////////////////////////////////////////////////////////////
class TestApp : public DWI::App
{

/////////////////////////////////////////////////////////////////
protected:

	int				__numberOfRenders;
	int				__maxNumberOfRenders;
	stringstream	__sstream;



/////////////////////////////////////////////////////////////////
public:

	/////////////////////////////////////////////
	// ctor and dtor

	TestApp( void );
	virtual ~TestApp( void );


	/////////////////////////////////////////////
	// Event callback overrides

	/**
	* This function is called by eventStart() when the game engine starts.
	*/
	virtual void onStart( void );

	/**
	* This function is called by eventPreRender() when a pre-render stage occurs.
	*/
	virtual void onPreRender( void );

	/**
	* This function is called by eventRender() when a render stage occurs.
	*/
	virtual void onRender( void );

	/**
	* This function is called by eventPostRender() when a post-render stage occurs.
	*/
	virtual void onPostRender( void );

	/**
	* This function is called by eventStop() when the game engine stops.
	*/
	virtual void onStop( void );
};

#endif // TESTAPP
