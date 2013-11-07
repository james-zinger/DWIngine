#ifndef DWI_Log
#define DWI_Log

#include <fstream>
#include <string>

using namespace std;



namespace DWI
{
	///////////////////////////////////////////////////////////////////////////////////////////////////
	enum LogLevel
	{
		DWI_NONE = 0,
		DWI_TRACE,
		DWI_ERROR,
		DWI_WARN,
		DWI_INFO,
		DWI_ALL
	};


	///////////////////////////////////////////////////////////////////////////////////////////////////
	class Log
	{

	/////////////////////////////////////////////////////////////////
	private: 
	
		/////////////////////////////////////////////
		// Singleton variable

		static Log* __singleton;


		/////////////////////////////////////////////
		// Private member variables

		string		__filename;
		ofstream*	__fileStream;
		bool		__printToConsole;
		LogLevel	__outputLevel;


		/////////////////////////////////////////////
		// ctor and dtor

		Log( void );
		~Log( void );

	
	
	/////////////////////////////////////////////////////////////////
	public:
	
		/////////////////////////////////////////////
		// Singleton ctor and dtor

		/**
		*
		* @returns
		*/
		static Log* singleton( void );

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

		/////////////////////////////////////////////
		// Static interface for singleton

		static void LogMessage	( LogLevel level, string message);
		static void LogError	( string message );
		static void LogTrace	( string message );
		static void LogInfo		( string message );
		static void LogWarn		( string message );

	};

	


}

#endif // DWI_Log
