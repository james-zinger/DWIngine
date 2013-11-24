#include "FlagApp.h"
#include "DWIngine.h"
#include <Windows.h>
/**
* This function is the entrypoint to the application.
*/

int main( int argc, char** argv )
{
	// Create the engine singleton and start it
	// It will maintain a loop on its own once it has started
	DWI::DWIngine::singleton()->start( new FlagApp() );

	// Destroy the DWIngine instance and release its heap memory
	DWI::DWIngine::destroySingleton();

	// Return with a healthy error code
	return 0;
}