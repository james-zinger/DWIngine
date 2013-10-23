#ifndef DWI_OBJECTCOULDNOTBECREATEDEXCEPTION
#define DWI_OBJECTCOULDNOTBECREATEDEXCEPTION

#include <exception>
#include <string>

using std::exception;
using std::string;



namespace DWI
{
	///////////////////////////////////////////////////////////////////////////////////////////////
	class ObjectCouldNotBeCreatedException : public exception
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

		ObjectCouldNotBeCreatedException( void );
		ObjectCouldNotBeCreatedException( const string message );
		ObjectCouldNotBeCreatedException( const string message, const void* context );
		~ObjectCouldNotBeCreatedException( void );


		/////////////////////////////////////////
		// Getters

		/*
		* Returns the address of the object that threw the exception.
		*/
		void* context( void );

	};
}

#endif // DWI_OBJECTCOULDNOTBECREATEDEXCEPTION
