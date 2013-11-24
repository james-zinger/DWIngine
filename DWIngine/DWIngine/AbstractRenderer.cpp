#include "AbstractRenderer.h"

namespace DWI
{
	///////////////////////////////////////////////////////////////////////////////////////////////////
	// Public

	/////////////////////////////////////////////////////////////////
	// ctor and dtor

	AbstractRenderer::AbstractRenderer( DWI::DWIngine* engine ) : __engine( engine )
	{

	}

	AbstractRenderer::~AbstractRenderer( void )
	{
		// No resources to release
	}


	/////////////////////////////////////////
	// Getters

	const DWIngine* DWI::AbstractRenderer::engine( void )
	{
		return __engine;
	}

	unsigned int DWI::AbstractRenderer::screenHeight( void )
	{
		return __screenHeight;
	}

	unsigned int DWI::AbstractRenderer::screenWidth( void )
	{
		return __screenWidth;
	}


	void DWI::AbstractRenderer::setScreenDimensions( int width, int height )
	{
		__screenHeight = height;
		__screenWidth = width;
	}

	Camera* DWI::AbstractRenderer::getCamera( void )
	{
		return &__cam;
	}

}