#include <stdlib.h>
#include <iostream>
#include <string>
#include "HardwareClock.h"
#include "LogManager.h"

using namespace std;

int main( int argc, char** argv )
{
	cout << "Instantiate HardwareClock singleton..." << endl;

	HardwareClock* clock = HardwareClock::singleton();

	cout << "HardwareClock ready!" << endl;
	cout << "Test 1,000,000 refreshes..." << endl;

	cout << "CPU Clockspeed: " << clock->currentHz() << "Hz  ::  Current time: " << clock->appTime() << "s" << endl;

	int i = 0;
	for ( i = 0; i < 1000000; i++ )
	{
		//cout << "CPU Clockspeed: " << clock->currentHz() << "Hz  ::  Current time: " << clock->appTime() << "s" << endl;
		clock->refresh( true );
	}

	cout << "CPU Clockspeed: " << clock->currentHz() << "Hz  ::  Current time: " << clock->appTime() << "s" << endl;

	for ( i = 0; i < 1000000; i++ )
	{
		//cout << "CPU Clockspeed: " << clock->currentHz() << "Hz  ::  Current time: " << clock->appTime() << "s" << endl;
		clock->refresh( false );
	}

	cout << "CPU Clockspeed: " << clock->currentHz() << "Hz  ::  Current time: " << clock->appTime() << "s" << endl;
	cout << "Testing LogManager with a warning..." << endl;
	cout << "(Go check DWILog.log)" << endl;

	LogManager* logman = LogManager::GetInstance();
	logman->setOutPutLevel( LogManager::WARN );
	logman->LogError( "Testing" );

	cin >> i;

	return 0;
}