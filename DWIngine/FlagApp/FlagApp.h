#ifndef TESTAPP
#define TESTAPP

#include <sstream>
#include "App.h"
#include "Cloth.h"
#include "GameObject.h"
#define WIND_TIME 5.0f

using namespace std;



///////////////////////////////////////////////////////////////////////////////////////////////////
class FlagApp : public DWI::App
{

/////////////////////////////////////////////////////////////////
protected:

	bool			__isStarting;
	Cloth			__cloth;
	stringstream	__sstream;
	DWI::GameObject*		__parent;


/////////////////////////////////////////////////////////////////
public:

	/////////////////////////////////////////////
	// ctor and dtor

	FlagApp( void );
	virtual ~FlagApp( void );


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
