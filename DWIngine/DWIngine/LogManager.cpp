#include <iostream>
#include <fstream>
#include "LogManager.h"

#ifndef NULL
#define NULL 0
#endif



///////////////////////////////////////////////////////////////////////////////////////////////////
// Private

/////////////////////////////////////////////////////////////////
// Singleton variable

LogManager* LogManager::__singleton = NULL;


/////////////////////////////////////////////////////////////////
// ctor and dtor

LogManager::LogManager( void )
{
	__outputLevel = LogLevel::ALL;
	__filename = "DWIngine.log";
	ofstream* file = new ofstream();
	file->open( __filename, ios_base::out );
	__fileStream = file;
}


LogManager::~LogManager(void)
{
	closeFile();
}



///////////////////////////////////////////////////////////////////////////////////////////////////
// Public

/////////////////////////////////////////////////////////////////
// Singleton ctor and dtor

LogManager* LogManager::singleton( void )
{
	if ( __singleton == NULL )
	{
		__singleton = new LogManager();
	}

	return __singleton;
}

void LogManager::destroySingleton( void )
{
	if ( __singleton != NULL )
	{
		delete __singleton;
		__singleton = NULL;
	}
}


/////////////////////////////////////////////////////////////////
// Logging API

void LogManager::log( LogLevel level, const string& message )
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

void LogManager::logError( const string& message )
{
	log( LogLevel::ERROR, message );
}

void LogManager::logInfo( const string& message )
{
	log( LogLevel::INFO, message );
}

void LogManager::logTrace( const string& message )
{
	log( LogLevel::TRACE, message );
}

void LogManager::logWarn( const string& message )
{
	log( LogLevel::WARN, message );
}


/////////////////////////////////////////////////////////////////
// File operations

void LogManager::closeFile( void )
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

LogLevel LogManager::outputLevel( void )
{
	return __outputLevel;
}

string& LogManager::filename( void )
{
	return __filename;
}

	
/////////////////////////////////////////////////////////////////
// Private variable setters

void LogManager::outputLevel( const LogLevel value )
{
	__outputLevel = value;
}

void LogManager::filename( const string value )
{
	closeFile();
	__filename = value;
	__fileStream = new ofstream( __filename );
	
}
