#include "AbstractRenderer.h"

using DWI::AbstractRenderer;

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
////////////////////////////////////////////
// Public Common Functions
// Register Functions
void AbstractRenderer::registerModel( DWI::Model* model )
{
	__models[model->getID()] = model;
}

void AbstractRenderer::deregisterModel( int key )
{
	__models.erase( key );
}

void AbstractRenderer::deregisterModel( DWI::Model* model )
{
	__models.erase( model->getID() );
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


void DWI::AbstractRenderer::setScreenDimensions( int width, int height )
{
	__screenHeight = height;
	__screenWidth = width;
}