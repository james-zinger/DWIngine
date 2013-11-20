#include <math.h>
#include "Cloth.h"

#ifndef NULL
#define NULL 0
#endif

#define CLOTH_SQRT2 1.4142135623730950488016887242097



///////////////////////////////////////////////////////////////////////////////////////////////////
// Private

/////////////////////////////////////////////////////////////////
// Springs

void DWI::Cloth::applySpringForce( int index )
{
	Vector3 forceNode1ToNode2 = computeSpringForce( index );
	__springs[ index ].node1->force += forceNode1ToNode2;
	__springs[ index ].node2->force -= forceNode1ToNode2;
}

Vector3 DWI::Cloth::computeSpringForce( int index )
{
	// Get the normalized direction of the force vector
	Vector3 direction = __springs[ index ].node2->position - __springs[ index ].node1->position;
	float distance = direction.length();
	direction /= distance;

	// Return the force vector adjusted for magnitude
	return direction * __springCoeff * ( distance - __equilibriumDistance );
}


///////////////////////////////////////////////////////////////////////////////////////////////////
// Public 

/////////////////////////////////////////////////////////////////
// ctor and dtor

DWI::Cloth::Cloth( int rows, int columns, float equilibriumDistance, float nodeMass, float springCoeff, float dampingCoeff )
{
	init( rows, columns, equilibriumDistance, nodeMass, springCoeff, dampingCoeff );
}

DWI::Cloth::Cloth( void )
{
	reset();
}

DWI::Cloth::~Cloth( void )
{
	
}


/////////////////////////////////////////////////////////////////
// Initialization

void DWI::Cloth::init( int rows, int columns, float equilibriumDistance, float nodeMass, float springCoeff, float dampingCoeff )
{
	// Read in the necessary values
	__ready = true;
	__rows = rows;
	__columns = columns;
	__equilibriumDistance = equilibriumDistance;
	__nodeMass = nodeMass;
	__springCoeff = springCoeff;
	__dampingCoeff = dampingCoeff;
	
	// Builld the nodes list
	createNodes( __rows, __columns, __equilibriumDistance );

	// Build the springs list
	createSprings( __rows, __columns, __nodes );
}

void DWI::Cloth::reset( void )
{
	// Zero out all values
	__ready = false;
	__rows = 0;
	__columns = 0;
	__equilibriumDistance = 0.0f;
	__nodeMass = 0.0f;
	__springCoeff = 0.0f;
	__dampingCoeff = 0.0f;

	// Clear the nodes and springs lists
	__nodes.clear();
	__springs.clear();
}

void DWI::Cloth::createNodes( int rows, int columns, int equilibriumDistance )
{
	for ( int col = 0; col < columns; col++ )
	{
		for ( int row = 0; row < rows; row++ )
		{
			Node node;
			node.force = Vector3( 0, 0, 0 );
			node.acceleration = Vector3( 0, 0, 0 );
			node.velocity = Vector3( 0, 0, 0 );
			node.position = Vector3( col * equilibriumDistance, -row * equilibriumDistance, 0 );
			node.locked = false;
			__nodes.push_back( node );
		}
	}
}

void DWI::Cloth::createSprings( int rows, int columns, vector<Node>& nodes )
{
	int numberOfSprings = 4 * ( ( columns - 1 ) * ( rows - 1 ) ) + ( columns - 1 ) + ( rows - 1 );

	for ( int col = 0; col < columns; col++ )
	{
		for ( int row = 0; row < rows; row++ )
		{
			Spring spring;
			int nodeIndex = row * columns + col;
			bool isLastCol = ( col == columns - 1 );
			bool isLastRow = ( row == rows - 1 );

			if ( isLastCol && isLastRow )
			{
				// Do nothing! All spring relations have been made!
			}
			else if ( isLastCol )
			{
				// Create 1 Vertical Spring
				spring.node1 = &__nodes[ nodeIndex ];
				spring.node2 = &__nodes[ nodeIndex + columns ];
				spring.isDiagonal = false;
				__springs.push_back( spring );
			}
			else if ( isLastRow )
			{
				// Create 1 Horizontal Spring
				spring.node1 = &__nodes[ nodeIndex ];
				spring.node2 = &__nodes[ nodeIndex + 1 ];
				spring.isDiagonal = false;
				__springs.push_back( spring );
			}
			else
			{
				// Create 4 springs -- Vertical, Horizontal and 2 Diagonal

				// Create 1 Vertical Spring
				spring.node1 = &__nodes[ nodeIndex ];
				spring.node2 = &__nodes[ nodeIndex + columns ];
				spring.isDiagonal = false;
				__springs.push_back( spring );

				// Create 1 Horizontal Spring
				spring.node1 = &__nodes[ nodeIndex ];
				spring.node2 = &__nodes[ nodeIndex + 1 ];
				spring.isDiagonal = false;
				__springs.push_back( spring );

				// Create a TL to BR diagonal spring
				spring.node1 = &__nodes[ nodeIndex ];
				spring.node2 = &__nodes[ nodeIndex + columns + 1 ];
				spring.isDiagonal = true;
				__springs.push_back( spring );

				// Create a BL to TR diagonal spring
				spring.node1 = &__nodes[ nodeIndex + 1 ];
				spring.node2 = &__nodes[ nodeIndex + columns ];
				spring.isDiagonal = true;
				__springs.push_back( spring );
			}
		}
	}
}


/////////////////////////////////////////////////////////////////
// Dynamics

void DWI::Cloth::applyForceToNode( int index, Vector3 force )
{
	__nodes[ index ].force += force;
}


/////////////////////////////////////////////////////////////////
// Getters

int DWI::Cloth::columns( void )
{
	return __columns;
}

int DWI::Cloth::rows( void )
{
	return __rows;
}

vector<DWI::Node>& DWI::Cloth::nodes( void )
{
	return __nodes;
}

vector<DWI::Spring>& DWI::Cloth::springs( void )
{
	return __springs;
}

float DWI::Cloth::dampingCoeff( void )
{
	return __dampingCoeff;
}

float DWI::Cloth::equilibriumDistance( void )
{
	return __equilibriumDistance;
}

float DWI::Cloth::nodeMass( void )
{
	return __nodeMass;
}

float DWI::Cloth::springCoeff( void )
{
	return __springCoeff;
}


/////////////////////////////////////////////////////////////////
// Setters

void DWI::Cloth::dampingCoeff( float value )
{
	__dampingCoeff = value;
}

void DWI::Cloth::equilibriumDistance( float value )
{
	__equilibriumDistance = value;
}

void DWI::Cloth::nodeMass( float value )
{
	__nodeMass = value;
}

void DWI::Cloth::springCoeff( float value )
{
	__springCoeff = value;
}