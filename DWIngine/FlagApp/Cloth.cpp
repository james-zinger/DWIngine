#include <math.h>
#include "MeshAsset.h"
#include "Cloth.h"
#include "Log.h"
#include <sstream>

#ifndef NULL
#define NULL 0
#endif

#define CLOTH_SQRT2 1.4142136

using DWI::MeshAsset;



///////////////////////////////////////////////////////////////////////////////////////////////////
// Private

/////////////////////////////////////////////////////////////////
// Initialization

void Cloth::createNodes( int rows, int columns, float equilibriumDistance )
{
	for ( int row = 0; row < rows; row++ )
	{
		for ( int col = 0; col < columns; col++ )
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

void Cloth::createSprings( int rows, int columns, vector<Node>& nodes )
{
	for ( int row = 0; row < rows; row++ )
	{
		for ( int col = 0; col < columns; col++ )
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

				// Create 1 TL to BR diagonal spring
				spring.node1 = &__nodes[ nodeIndex ];
				spring.node2 = &__nodes[ nodeIndex + columns + 1 ];
				spring.isDiagonal = true;
				__springs.push_back( spring );

				// Create 1 BL to TR diagonal spring
				//spring.node1 = &__nodes[ nodeIndex + 1 ];
				//spring.node2 = &__nodes[ nodeIndex + columns ];
				//spring.isDiagonal = true;
				//__springs.push_back( spring );
			}
		}
	}
}

void Cloth::startGeometry( int rows, int columns, float equilibriumDistance, vector<Node>& nodes )
{
	vector<Vector3>& normals = __meshComponent->meshAsset()->normals();
	vector<Vector2>& uvs = __meshComponent->meshAsset()->uvs();
	vector<Vector3>& vertices = __meshComponent->meshAsset()->vertices();

	normals.clear();
	uvs.clear();
	vertices.clear();
	
	for ( int row = 0; row < ( rows - 1 ); row++ )
	{
		for ( int col = 0; col < ( columns - 1 ); col++ )
		{
			for ( int i = 0; i < 12; i++ )
			{
				normals.push_back( Vector3( 0, 0, 0 ) );
				uvs.push_back( Vector2( 0, 0 ) );
				vertices.push_back( Vector3( 0, 0, 0 ) );
			}
		}
	}

	// Set the UVs for the first time
	setMeshUVs( rows, columns, equilibriumDistance, nodes, uvs );
}


/////////////////////////////////////////////////////////////////
// Physics

void Cloth::applySpringForce( int index )
{
	Vector3 forceNode1ToNode2 = computeSpringForce( index );
	__springs[ index ].node1->force += forceNode1ToNode2;
	__springs[ index ].node2->force -= forceNode1ToNode2;
}

Vector3 Cloth::computeSpringForce( int index )
{
	// Get the normalized direction of the force vector
	Vector3 direction = __springs[ index ].node2->position - __springs[ index ].node1->position;
	float distance = glm::length( direction );
	direction /= distance;

	// Limit the maximum spring distance by moving node2 closer
	float diagonalCoeff = __springs[ index ].isDiagonal ? CLOTH_SQRT2 : 1.0f;
	float overMax = distance - ( __maxDistance * diagonalCoeff );
	if ( overMax > 0.0f )
	{
		__springs[ index ].node2->position -= direction * overMax;
		distance = __maxDistance;
	}

	// Return the force vector adjusted for magnitude
	float difference = distance - ( __equilibriumDistance * diagonalCoeff );
	return direction * __springCoeff * difference;
}


/////////////////////////////////////////////////////////////////
// Dynamic meshing

void Cloth::setMeshNormals( int rows, int columns, vector<Node>& nodes, vector<Vector3>& normals )
{
	int normIndex = 0;
	Vector3 crossProduct;

	for ( int row = 0; row < ( rows - 1 ); row++ )
	{
		for ( int col = 0; col < ( columns - 1 ); col++ )
		{
			int nodeIndex = row * columns + col;
			Node* tl = &nodes[ nodeIndex ];
			Node* tr = &nodes[ nodeIndex + 1 ];
			Node* bl = &nodes[ nodeIndex + columns ];
			Node* br = &nodes[ nodeIndex + columns + 1 ];

			// Set up normals for the 2 front-facing triangles and the 2 back-facing triangles
			// that comprise this square region of the cloth.

			// Front-facing triangle: tl, bl, tr
			crossProduct = -glm::cross( bl->position - tl->position, tr->position - bl->position );
			normals[ normIndex++ ] = crossProduct;
			normals[ normIndex++ ] = crossProduct;
			normals[ normIndex++ ] = crossProduct;

			// Back-facing triangle: tl, tr, bl
			crossProduct = -glm::cross( tr->position - tl->position, bl->position - tr->position );
			normals[ normIndex++ ] = crossProduct;
			normals[ normIndex++ ] = crossProduct;
			normals[ normIndex++ ] = crossProduct;

			// Front-facing triangle: tr, bl, br
			crossProduct = -glm::cross( bl->position - tr->position, br->position - bl->position );
			normals[ normIndex++ ] = crossProduct;
			normals[ normIndex++ ] = crossProduct;
			normals[ normIndex++ ] = crossProduct;

			// Back-facing triangle: tr, br, bl
			crossProduct = -glm::cross( br->position - tr->position, bl->position - br->position );
			normals[ normIndex++ ] = crossProduct;
			normals[ normIndex++ ] = crossProduct;
			normals[ normIndex++ ] = crossProduct;
		}
	}
}

void Cloth::setMeshUVs( int rows, int columns, float equilibriumDistance, vector<Node>& nodes, vector<Vector2>& uvs )
{
	int uvIndex = 0;
	float width = columns * equilibriumDistance;
	float height = rows * equilibriumDistance;

	for ( int row = 0; row < ( rows - 1 ); row++ )
	{
		for ( int col = 0; col < ( columns - 1 ); col++ )
		{
			int nodeIndex = row * columns + col;
			Node* tl = &nodes[ nodeIndex ];
			Node* tr = &nodes[ nodeIndex + 1 ];
			Node* bl = &nodes[ nodeIndex + columns ];
			Node* br = &nodes[ nodeIndex + columns + 1 ];
			Vector2 tlUV( ( tl->position.x + 1.5f * equilibriumDistance ) / width, tl->position.y / height );
			Vector2 trUV( ( tr->position.x + 1.5f * equilibriumDistance ) / width, tr->position.y / height );
			Vector2 blUV( ( bl->position.x + 1.5f * equilibriumDistance ) / width, bl->position.y / height );
			Vector2 brUV( ( br->position.x + 1.5f * equilibriumDistance ) / width, br->position.y / height );

			// Set up uvs for the 2 front-facing triangles and the 2 back-facing triangles
			// that comprise this square region of the cloth.

			// Front-facing triangle: tl, bl, tr
			uvs[ uvIndex++ ] = tlUV;
			uvs[ uvIndex++ ] = blUV;
			uvs[ uvIndex++ ] = trUV;

			// Back-facing triangle: tl, tr, bl
			uvs[ uvIndex++ ] = tlUV;
			uvs[ uvIndex++ ] = trUV;
			uvs[ uvIndex++ ] = blUV;

			// Front-facing triangle: tr, bl, br
			uvs[ uvIndex++ ] = trUV;
			uvs[ uvIndex++ ] = blUV;
			uvs[ uvIndex++ ] = brUV;

			// Back-facing triangle: tr, br, bl
			uvs[ uvIndex++ ] = trUV;
			uvs[ uvIndex++ ] = brUV;
			uvs[ uvIndex++ ] = blUV;
		}
	}
}

void Cloth::setMeshVertices( int rows, int columns, vector<Node>& nodes, vector<Vector3>& vertices )
{
	int vertIndex = 0;

	for ( int row = 0; row < ( rows - 1 ); row++ )
	{
		for ( int col = 0; col < ( columns - 1 ); col++ )
		{
			int nodeIndex = row * columns + col;
			Node* tl = &nodes[ nodeIndex ];
			Node* tr = &nodes[ nodeIndex + 1 ];
			Node* bl = &nodes[ nodeIndex + columns ];
			Node* br = &nodes[ nodeIndex + columns + 1 ];

			// Set up vertices for the 2 front-facing triangles and the 2 back-facing triangles
			// that comprise this square region of the cloth.
			
			// Front-facing triangle: tl, bl, tr
			vertices[ vertIndex++ ] = tl->position;
			vertices[ vertIndex++ ] = bl->position;
			vertices[ vertIndex++ ] = tr->position;

			// Back-facing triangle: tl, tr, bl
			vertices[ vertIndex++ ] = tl->position;
			vertices[ vertIndex++ ] = tr->position;
			vertices[ vertIndex++ ] = bl->position;

			// Front-facing triangle: tr, bl, br
			vertices[ vertIndex++ ] = tr->position;
			vertices[ vertIndex++ ] = bl->position;
			vertices[ vertIndex++ ] = br->position;

			// Back-facing triangle: tr, br, bl
			vertices[ vertIndex++ ] = tr->position;
			vertices[ vertIndex++ ] = br->position;
			vertices[ vertIndex++ ] = bl->position;
		}
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////////
// Public 

/////////////////////////////////////////////////////////////////
// ctor and dtor

Cloth::Cloth( Mesh* meshComponent, int rows, int columns, float equilibriumDistance, float maxDistance, float nodeMass, float springCoeff, float dampingCoeff )
{
	__meshComponent = meshComponent;
	init( rows, columns, equilibriumDistance, maxDistance, nodeMass, springCoeff, dampingCoeff );
}

Cloth::Cloth( void )
{
	__meshComponent = NULL;
	reset();
}

Cloth::~Cloth( void )
{
	
}


/////////////////////////////////////////////////////////////////
// Initialization

void Cloth::init( int rows, int columns, float equilibriumDistance, float maxDistance, float nodeMass, float springCoeff, float dampingCoeff )
{
	// Read in the necessary values
	__ready = true;
	__rows = rows;
	__columns = columns;
	__equilibriumDistance = equilibriumDistance;
	__maxDistance = maxDistance;
	__nodeMass = nodeMass;
	__springCoeff = springCoeff;
	__dampingCoeff = dampingCoeff;
	
	// Build the nodes list
	createNodes( rows, columns, equilibriumDistance );

	// Build the springs list
	createSprings( rows, columns, __nodes );

	// Start the mesh geometry by sizing the vectors correctly
	startGeometry( rows, columns, equilibriumDistance, __nodes );

	// Push the geometry out to the mesh component for the first time
	updateMesh();

	// Push the mesh out to the graphics card for the first time
	__meshComponent->meshAsset()->init();
}

void Cloth::reset( void )
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

	// Clear the geometry from the mesh component
	if ( __meshComponent != NULL )
	{
		__meshComponent->meshAsset()->normals().clear();
		__meshComponent->meshAsset()->uvs().clear();
		__meshComponent->meshAsset()->vertices().clear();
	}
}


/////////////////////////////////////////////////////////////////
// Update

void Cloth::update( float dt )
{
	updatePhysics( dt );
	updateMesh();
}

void Cloth::updatePhysics( float dt )
{
	// Spring-wise force analysis to determine the new net force of each node
	for ( unsigned int springIndex = 0; springIndex < __springs.size(); springIndex++ )
	{
		applySpringForce( springIndex );
	}

	// Integrate acceleration, velocity and position for each node after forces 
	// have been computed.
	// Note: If this is done in the loop above, forces will be calculated incorrectly!
	for ( unsigned int nodeIndex = 0; nodeIndex < __nodes.size(); nodeIndex++ )
	{
		// If this node's position is locked then skip this iteration
		if ( __nodes[ nodeIndex ].locked ) continue;

		// Determine acceleration from mass and net force
		__nodes[ nodeIndex ].acceleration = dt * __nodes[ nodeIndex ].force / __nodeMass;

		// Integrate velocity and apply damping
		__nodes[ nodeIndex ].velocity += dt * __nodes[ nodeIndex ].acceleration;
		__nodes[ nodeIndex ].velocity /= __dampingCoeff + 1.0;

		// Integrate position
		__nodes[ nodeIndex ].position += dt * __nodes[ nodeIndex ].velocity;
	}

	// Clear the net forces on each node -- we need to start from scratch
	// Note: This is done last so forces can be added to the cloth by the end-user
	// during other code on each update.
	for ( unsigned int nodeIndex = 0; nodeIndex < __nodes.size(); nodeIndex++ )
	{
		__nodes[ nodeIndex ].force = Vector3( 0, 0, 0 );
	}
}

void Cloth::updateMesh( void )
{
	MeshAsset* meshAsset = __meshComponent->meshAsset();

	// Update the vertices and normals in RAM
	setMeshVertices( __rows, __columns, __nodes, meshAsset->vertices() );
	setMeshNormals( __rows, __columns, __nodes, meshAsset->normals() );

	// Push the updated mesh to the graphics card
	meshAsset->LoadGFXVertices();
	meshAsset->LoadGFXNormals();
}


/////////////////////////////////////////////////////////////////
// Physics

void Cloth::applyForceToNode( int index, Vector3 force )
{
	__nodes[ index ].force += force;
}


/////////////////////////////////////////////////////////////////
// Getters

int Cloth::columns( void )
{
	return __columns;
}

int Cloth::rows( void )
{
	return __rows;
}

vector<Node>& Cloth::nodes( void )
{
	return __nodes;
}

vector<Spring>& Cloth::springs( void )
{
	return __springs;
}

float Cloth::dampingCoeff( void )
{
	return __dampingCoeff;
}

float Cloth::equilibriumDistance( void )
{
	return __equilibriumDistance;
}

float Cloth::nodeMass( void )
{
	return __nodeMass;
}

float Cloth::springCoeff( void )
{
	return __springCoeff;
}


/////////////////////////////////////////////////////////////////
// Setters

void Cloth::meshComponent( Mesh* value )
{
	__meshComponent = value;
}

void Cloth::dampingCoeff( float value )
{
	__dampingCoeff = value;
}

void Cloth::equilibriumDistance( float value )
{
	__equilibriumDistance = value;
}

void Cloth::nodeMass( float value )
{
	__nodeMass = value;
}

void Cloth::springCoeff( float value )
{
	__springCoeff = value;
}