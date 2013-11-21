#include "Time.h"
#include <Windows.h>

#ifndef NULL
#define NULL 0
#endif



///////////////////////////////////////////////////////////////////////////////////////////////////
// Private

/////////////////////////////////////////////////////////////////
// Singleton variable

DWI::Time* DWI::Time::__singleton = NULL;


/////////////////////////////////////////////////////////////////
// ctor and dtor

DWI::Time::Time( void )
{
	// Zero out the values set by refresh()
	__currentHz			= 0L;
	__currentTicks		= 0L;
	__hiResSupported	= false;
	__previousTicks		= 0L;

	// Refresh the first time to collect the current CPU tick count and consider that as the starting CPU tick count
	refresh( true );
	__startTicks = __currentTicks;

	// Zero out appTime after since it can't be incremented accurately until both currentTicks and startTicks are set
	__currentAppTime = 0.0;
	__previousAppTime = 0.0;
	__dt = 0.0;
}

DWI::Time::~Time( void )
{
	// No resources to release
}



///////////////////////////////////////////////////////////////////////////////////////////////////
// Public

/////////////////////////////////////////////////////////////////
// Singleton ctor and dtor

DWI::Time* DWI::Time::singleton( void )
{
	if ( __singleton == NULL )
	{
		__singleton = new Time();
	}

	return __singleton;
}

void DWI::Time::destroySingleton( void )
{
	if ( __singleton != NULL )
	{
		delete __singleton;
		__singleton = NULL;
	}
}


/////////////////////////////////////////////////////////////////
// Refresh

void DWI::Time::refresh( bool updateHz )
{
	LARGE_INTEGER temp;
	
	// Fetch the latest CPU clock frequency
	if ( updateHz )
	{
		int tempbool = QueryPerformanceFrequency( &temp );
		__hiResSupported = tempbool == 0;
		
		__currentHz = (long)temp.QuadPart;
	}

	// Fetch the latest CPU tick count
	QueryPerformanceCounter( &temp );
	__currentTicks = (long)temp.QuadPart;

	// Use the above and startTicks to increment the clock
	__dt = (double)( __currentTicks - __previousTicks ) / (double)__currentHz;
	double newTime = __currentAppTime + __dt;

	// Store the previous measurements
	__previousAppTime = __currentAppTime;
	__previousTicks = __currentTicks;

	// Store the current measurement
	__currentAppTime = newTime;
}


/////////////////////////////////////////////////////////////////
// Getters

double DWI::Time::currentAppTime( void ) 
{
	return __currentAppTime;
}

double DWI::Time::currentAppTimeMS( void )
{
	return __currentAppTime * 1000.0;
}

long DWI::Time::currentHz( void )
{
	return __currentHz;
}

double DWI::Time::dt( void ) 
{
	return __dt;
}

double DWI::Time::dtMS( void ) 
{
	return __dt * 1000.0;
}

long DWI::Time::currentTicks( void )
{
	return __currentTicks;
}

bool DWI::Time::hiResSupported( void )
{
	return __hiResSupported;
}

double DWI::Time::previousAppTime( void ) 
{
	return __previousAppTime;
}

double DWI::Time::previousAppTimeMS( void )
{
	return __previousAppTime * 1000.0;
}

long DWI::Time::previousTicks( void )
{
	return __previousTicks;
}

long DWI::Time::startTicks( void )
{
	return __startTicks;
}
