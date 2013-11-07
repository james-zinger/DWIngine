#include <iostream>
#include <fstream>
#include "Log.h"

#ifndef NULL
#define NULL 0
#endif



///////////////////////////////////////////////////////////////////////////////////////////////////
// Private

/////////////////////////////////////////////////////////////////
// Singleton variable

DWI::Log* DWI::Log::__singleton = NULL;


/////////////////////////////////////////////////////////////////
// ctor and dtor

DWI::Log::Log( void )
{
	__outputLevel = LogLevel::DWI_ALL;
	__filename = "DWIngine.log";
	ofstream* file = new ofstream();
	file->open( __filename, ios_base::out );
	__fileStream = file;
}


DWI::Log::~Log(void)
{
	closeFile();
}



///////////////////////////////////////////////////////////////////////////////////////////////////
// Public

/////////////////////////////////////////////////////////////////
// Singleton ctor and dtor

DWI::Log* DWI::Log::singleton( void )
{
	if ( __singleton == NULL )
	{
		__singleton = new Log();
	}

	return __singleton;
}

void DWI::Log::destroySingleton( void )
{
	if ( __singleton != NULL )
	{
		delete __singleton;
		__singleton = NULL;
	}
}


/////////////////////////////////////////////////////////////////
// Logging API

void DWI::Log::log( LogLevel level, const string& message )
{
	if ( level <= __outputLevel )
	{
		if ( __fileStream != NULL )
		{
			*__fileStream << message << "\n";
			__fileStream->flush();
		}
	}
}

void DWI::Log::logError( const string& message )
{
	log( LogLevel::DWI_ERROR, message );
}

void DWI::Log::logInfo( const string& message )
{
	log( LogLevel::DWI_INFO, message );
}

void DWI::Log::logTrace( const string& message )
{
	log( LogLevel::DWI_TRACE, message );
}

void DWI::Log::logWarn( const string& message )
{
	log( LogLevel::DWI_WARN, message );
}


/////////////////////////////////////////////////////////////////
// File operations

void DWI::Log::closeFile( void )
{
	if ( __fileStream != NULL )
	{
		__fileStream->close();
		delete __fileStream;
		__fileStream = NULL;
	}
}


/////////////////////////////////////////////////////////////////
// Private variable getters

DWI::LogLevel DWI::Log::outputLevel( void )
{
	return __outputLevel;
}

string& DWI::Log::filename( void )
{
	return __filename;
}

	
/////////////////////////////////////////////////////////////////
// Private variable setters

void DWI::Log::outputLevel( const LogLevel value )
{
	__outputLevel = value;
}

void DWI::Log::filename( const string value )
{
	closeFile();
	__filename = value;
	__fileStream = new ofstream( __filename );
	
}

/////////////////////////////////////////////
// Static interface for singleton

void DWI::Log::LogMessage( DWI::LogLevel level, string message )
{
	DWI::Log::singleton()->log(level, message);
}

void DWI::Log::LogError( string message )
{
	DWI::Log::singleton()->logError( message );
}

void DWI::Log::LogWarn( string message )
{
	DWI::Log::singleton()->logWarn( message );
}

void DWI::Log::LogTrace( string message )
{
	DWI::Log::singleton()->logTrace( message );
}

void DWI::Log::LogInfo( string message )
{
	DWI::Log::singleton()->logInfo( message );
}