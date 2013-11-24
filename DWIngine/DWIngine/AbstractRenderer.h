#ifndef DWI_ABSTRACTRENDERER
#define DWI_ABSTRACTRENDERER

#include "Mesh.h"
#include "Camera.h"
namespace DWI
{
	// Forward includes
	class DWIngine;

	///////////////////////////////////////////////////////////////////////////////////////////////
	class AbstractRenderer
	{

		////////////////////////////////////////////////////////////////
	protected:

		//////////////////////////////////////////
		// Protected member variables

		const DWIngine*	__engine;
		unsigned int	__screenHeight;
		unsigned int	__screenWidth;

		Camera __cam;

		/////////////////////////////////////////////////////////////
	public:

		/////////////////////////////////////////
		// ctor and dtor

		AbstractRenderer( DWIngine* engine );
		virtual ~AbstractRenderer( void );


		//////////////////////////////////////////
		// Public abstract functions

		virtual void renderScene( void ) = 0;

		/////////////////////////////////////////
		// Getters

		/*
		* Return the engine to which this app is currently attached.
		*/
		const DWIngine* engine( void );

		/*
		* Return the screen height to which the renderer is displaying.
		*/
		unsigned int screenHeight( void );

		/*
		* Return the screen width to which the renderer is displaying.
		*/
		unsigned int screenWidth( void );

		void setScreenDimensions( int width, int height );

		virtual Camera* getCamera( void );
	};
}

#endif // DWI_ABSTRACTRENDERER
