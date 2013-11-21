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
:* L
		 * @return	Pointer to the HardwareClock instance.
		 */
		static Time* singleton( void );

		/**
		 * Destroys the HardwareClock instance and releases it from heap memory.
		 */
		static void destroySingleton( void );


		/////////////////////////////////////////////
		// Update hardware ticks count value and time

		/**
		 * Updates the HardwareClock with a new reading from the CPU. This should be called frequently
		 * so that clockspeed fluctuations can be accounted for at a high sampling rate, as this will
		 * lead to better appTime estimation.
		 * @param	updateHz	true to use the high resolution clock.
		 */
		void refresh( bool updateHz );


		/////////////////////////////////////////////
		// Getters for private members

		/**
		 * Returns an estimation of the time since the HardwareClock was instantiated. Call refresh()
		 * frequently to ensure that this estimate is accurate.
		 * @return	Time, in seconds, since instantiation of the HardwareClock.
		 */
		double currentAppTime( void );

		/**
		 * Returns an estimation of the time since the HardwareClock was instantiated. Call refresh()
		 * frequently to ensure that this estimate is accurate.
		 * @return	Time, in milliseconds, since instantiation of the HardwareClock.
		 */
		double currentAppTimeMS( void );

		/**
		 * Returns the most current reading for the CPU's clockspeed.
		 * @return	Frequency, in Hz, at which the CPU processes operations recorded at the last
		 * 			refresh().
		 */
		long currentHz( void );

		/**
		 * Returns the most current reading of the CPU's tick count.
		 * @return	Number of operations the CPU had counted as of the most recent refresh().
		 */
		long currentTicks( void );

		/**
		 * Returns the time since the previous measurement of the app time.
		 * @return	Time, in seconds, since the previous measurement of the app time.
		 */
		double dt( void );

		/**
		 * Returns the time since the previous measurement of the app time.
		 * @return	Time, in milliseconds, since the previous measurement of the app time.
		 */
		double dtMS( void );

		/**
		 * Returns whether or not the hardware supports high-resolution timing.
		 * @return	TRUE if the CPU supports high-resolution timing, FALSE if it does not.
		 */
		bool hiResSupported( void );

		/**
		 * Returns an estimation of the time since the HardwareClock was instantiated as of the 2nd most
		 * recent measurement. Call refresh() frequently to ensure that this estimate is accurate.
		 * @return	Time, in seconds, since instantiation of the HardwareClock.
		 */
		double previousAppTime( void );

		/**
		 * @fn	double Time::previousAppTimeMS( void );
		 * @brief	Returns an estimation of the time since the HardwareClock was instantiated as of the
		 * 			2nd most recent measurement. Call refresh() frequently to ensure that this estimate
		 * 			is accurate.
		 * @return	Time, in milliseconds, since instantiation of the HardwareClock.
		 */
		double previousAppTimeMS( void );

		/**
		 * Returns the 2nd most current reading of the CPU's tick count.
		 * @return	Number of operations the CPU had counted as of the 2nd most recent refresh().
		 */
		long previousTicks( void );

		/**
		 * Returns the CPU tick count that was recorded when the HardwareClock was instantiated.
		 * @return	Number of operations the CPU had counted when the HardwareClock started.
		 */
		long startTicks( void );
	};
}

#endif // DWI_Time
