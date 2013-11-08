#ifndef DWI_ABSTRACTRENDERER
#define DWI_ABSTRACTRENDERER

#include "Mesh.h"
#include <map>
#include "Model.h"
using std::map;
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
		map<int, Model*>	__models;

		
	/////////////////////////////////////////////////////////////
	public:

		/////////////////////////////////////////
		// ctor and dtor

		AbstractRenderer( DWIngine* engine );
		virtual ~AbstractRenderer( void );


		//////////////////////////////////////////
		// Public abstract functions

		virtual void renderScene( void ) = 0;
		virtual void resize( const unsigned int width, const unsigned int height ) = 0;
		virtual void registerModel( Model* m );
		virtual void deregisterModel( Model* m );
		virtual void deregisterModel( int key );

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
	};
}

#endif // DWI_ABSTRACTRENDERER
