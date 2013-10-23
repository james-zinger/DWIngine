#include "AbstractRenderer.h"



///////////////////////////////////////////////////////////////////////////////////////////////////
// Public

/////////////////////////////////////////////////////////////////
// ctor and dtor

DWI::AbstractRenderer::AbstractRenderer( DWI::DWIngine* engine ) : __engine( engine )
{

}

DWI::AbstractRenderer::~AbstractRenderer( void )
{
	// No resources to release
}


/////////////////////////////////////////
// Getters

const DWI::DWIngine* DWI::AbstractRenderer::engine( void )
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