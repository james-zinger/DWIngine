#ifndef DWI_Time
#define DWI_Time



namespace DWI
{
	///////////////////////////////////////////////////////////////////////////////////////////////////
	class Time
	{

	/////////////////////////////////////////////////////////////////
	private:

		/////////////////////////////////////////////
		// Singleton variable

		static Time* __singleton;


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

		Time( void );
		~Time( void );



	/////////////////////////////////////////////////////////////////
	public:

		/////////////////////////////////////////////
		// Singleton ctor and dtor

		/**
		* Returns a pointer to the singleton instance of the Time.
		* @returns Pointer to the Time instance.
		*/
		static Time* singleton( void );

		/**
		* Destroys the Time instance and releases it from heap memory.
		*/
		static void destroySingleton( void );


		/////////////////////////////////////////////
		// Update hardware ticks count value and time

		/**
		* Updates the Time with a new reading from the CPU. This should be called frequently so that clockspeed
		* fluctuations can be accounted for at a high sampling rate, as this will lead to better appTime estimation.
		*/
		void refresh( bool updateHz );


		/////////////////////////////////////////////
		// Getters for private members

		/**
		* Returns an estimation of the time since the Time was instantiated. Call refresh() frequently to
		* ensure that this estimate is accurate.
		* @returns Time, in seconds, since instantiation of the Time.
		*/
		double currentAppTime( void );

		/**
		* Returns an estimation of the time since the Time was instantiated. Call refresh() frequently to
		* ensure that this estimate is accurate.
		* @returns Time, in milliseconds, since instantiation of the Time.
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
		* Returns an estimation of the time since the Time was instantiated as of the 2nd most recent measurement. 
		* Call refresh() frequently to ensure that this estimate is accurate.
		* @returns Time, in seconds, since instantiation of the Time.
		*/
		double previousAppTime( void );

		/**
		* Returns an estimation of the time since the Time was instantiated as of the 2nd most recent measurement. 
		* Call refresh() frequently to ensure that this estimate is accurate.
		* @returns Time, in milliseconds, since instantiation of the Time.
		*/
		double previousAppTimeMS( void );

		/**
		* Returns the 2nd most current reading of the CPU's tick count.
		* @returns Number of operations the CPU had counted as of the 2nd most recent refresh().
		*/
		long previousTicks( void );

		/**
		* Returns the CPU tick count that was recorded when the Time was instantiated.
		* @returns Number of operations the CPU had counted when the Time started.
		*/
		long startTicks( void );
	};
}

#endif // DWI_Time
