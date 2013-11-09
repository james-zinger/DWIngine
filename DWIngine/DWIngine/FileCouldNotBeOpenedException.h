#ifndef DWI_FILECOULDNOTBEOPENEDEXCEPTION
#define DWI_FILECOULDNOTBEOPENEDEXCEPTION

#include <exception>
#include <string>

using std::exception;
using std::string;



namespace DWI
{
	///////////////////////////////////////////////////////////////////////////////////////////////
	class FileCouldNotBeOpenedException : public exception
	{

	/////////////////////////////////////////////////////////////
	private:

		/////////////////////////////////////////
		// Private member variables

		const void* __context;


	/////////////////////////////////////////////////////////////
	public:

		/////////////////////////////////////////
		// ctor and dtor

		FileCouldNotBeOpenedException( void );
		FileCouldNotBeOpenedException( const string message );
		FileCouldNotBeOpenedException( const string message, const void* context );
		~FileCouldNotBeOpenedException( void );


		/////////////////////////////////////////
		// Getters

		/*
		* Returns the address of the object that threw the exception.
		*/
		void* context( void );

	};
}

#endif // DWI_FILECOULDNOTBEOPENEDEXCEPTION
