#ifndef DWI_HARDWARECLOCK
#define DWI_HARDWARECLOCK



namespace DWI
{
	///////////////////////////////////////////////////////////////////////////////////////////////////
	class HardwareClock
	{

	/////////////////////////////////////////////////////////////////
	private:

		/////////////////////////////////////////////
		// Singleton variable

		static HardwareClock* __singleton;


		/////////////////////////////////////////////
		// Private member variables

		double	__currentAppTime;
		long	__currentHz;
		long	__currentTicks;
		double	__dt;
		bool	__hiResSupported;
		double	__previousAppTime;
		long	__previousTicks;
		long	__startTicks;


		/////////////////////////////////////////////
		// ctor and dtor

		HardwareClock( void );
		~HardwareClock( void );



	/////////////////////////////////////////////////////////////////
	public:

		/////////////////////////////////////////////
		// Singleton ctor and dtor

		/**
		* Returns a pointer to the singleton instance of the HardwareClock.
		* @returns Pointer to the HardwareClock instance.
		*/
		static HardwareClock* singleton( void );

		/**
		* Destroys the HardwareClock instance and releases it from heap memory.
		*/
		static void destroySingleton( void );


		/////////////////////////////////////////////
		// Update hardware ticks count value and time

		/**
		* Updates the HardwareClock with a new reading from the CPU. This should be called frequently so that clockspeed
		* fluctuations can be accounted for at a high sampling rate, as this will lead to better appTime estimation.
		*/
		void refresh( bool updateHz );


		/////////////////////////////////////////////
		// Getters for private members

		/**
		* Returns an estimation of the time since the HardwareClock was instantiated. Call refresh() frequently to
		* ensure that this estimate is accurate.
		* @returns Time, in seconds, since instantiation of the HardwareClock.
		*/
		double currentAppTime( void );

		/**
		* Returns an estimation of the time since the HardwareClock was instantiated. Call refresh() frequently to
		* ensure that this estimate is accurate.
		* @returns Time, in milliseconds, since instantiation of the HardwareClock.
		*/
		double currentAppTimeMS( void );

		/**
		* Returns the most current reading for the CPU's clockspeed.
		* @returns Frequency, in Hz, at which the CPU processes operations recorded at the last refresh().
		*/
		long currentHz( void );

		/**
		* Returns the most current reading of the CPU's tick count.
		* @returns Number of operations the CPU had counted as of the most recent refresh().
		*/
		long currentTicks( void );

		/**
		* Returns the time since the previous measurement of the app time.
		* @returns Time, in seconds, since the previous measurement of the app time.
		*/
		double dt( void );

		/**
		* Returns the time since the previous measurement of the app time.
		* @returns Time, in milliseconds, since the previous measurement of the app time.
		*/
		double dtMS( void );

		/**
		* Returns whether or not the hardware supports high-resolution timing.
		* @returns TRUE if the CPU supports high-resolution timing, FALSE if it does not.
		*/
		bool hiResSupported( void );

		/**
		* Returns an estimation of the time since the HardwareClock was instantiated as of the 2nd most recent measurement. 
		* Call refresh() frequently to ensure that this estimate is accurate.
		* @returns Time, in seconds, since instantiation of the HardwareClock.
		*/
		double previousAppTime( void );

		/**
		* Returns an estimation of the time since the HardwareClock was instantiated as of the 2nd most recent measurement. 
		* Call refresh() frequently to ensure that this estimate is accurate.
		* @returns Time, in milliseconds, since instantiation of the HardwareClock.
		*/
		double previousAppTimeMS( void );

		/**
		* Returns the 2nd most current reading of the CPU's tick count.
		* @returns Number of operations the CPU had counted as of the 2nd most recent refresh().
		*/
		long previousTicks( void );

		/**
		* Returns the CPU tick count that was recorded when the HardwareClock was instantiated.
		* @returns Number of operations the CPU had counted when the HardwareClock started.
		*/
		long startTicks( void );
	};
}

#endif // DWI_HARDWARECLOCK
