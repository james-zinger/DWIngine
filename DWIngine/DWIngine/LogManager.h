#ifndef LOGMANAGER
#define LOGMANAGER

#include <fstream>
#include <string>

using namespace std;



///////////////////////////////////////////////////////////////////////////////////////////////////
enum LogLevel
{
	NONE = 0,
	TRACE,
	ERROR,
	WARN,
	INFO,
	ALL
};



///////////////////////////////////////////////////////////////////////////////////////////////////
class LogManager
{

/////////////////////////////////////////////////////////////////
private: 
	
	/////////////////////////////////////////////
	// Singleton variable

	static LogManager* __singleton;


	/////////////////////////////////////////////
	// Private member variables

	string		__filename;
	ofstream*	__fileStream;
	bool		__printToConsole;
	LogLevel	__outputLevel;


	/////////////////////////////////////////////
	// ctor and dtor

	LogManager( void );
	~LogManager( void );

	
	
/////////////////////////////////////////////////////////////////
public:
	
	/////////////////////////////////////////////
	// Singleton ctor and dtor

	/**
	*
	* @returns
	*/
	static LogManager* singleton( void );

	/**
	*
	*/
	static void destroySingleton( void );


	/////////////////////////////////////////////
	// Logging API

	/**
	*
	*/
	void log( LogLevel level, const string& message );

	/**
	*
	*/
	void logError( const string& message );

	/**
	*
	*/
	void logInfo( const string& message );

	/**
	*
	*/
	void logTrace( const string& message );

	/**
	*
	*/
	void logWarn( const string& message );


	/////////////////////////////////////////////
	// File operations

	/**
	*
	*/
	void closeFile( void );


	/////////////////////////////////////////////
	// Private variable getters

	/**
	*
	* @returns 
	*/
	LogLevel outputLevel( void );

	/**
	*
	* @returns 
	*/
	string& filename( void );

	
	/////////////////////////////////////////////
	// Private variable setters
	
	/**
	*
	*/
	void outputLevel( const LogLevel value );

	/**
	*
	*/
	void filename( const string value );
};

#endif // LOGMANAGER
