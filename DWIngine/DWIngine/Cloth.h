#ifndef DWI_CLOTH
#define DWI_CLOTH

#include <vector>
#include "DWMath.h"
#include "Mesh.h"

using std::vector;
using DWI::Vector3;



namespace DWI
{
	///////////////////////////////////////////////////////////////////////////////////////////////
	struct Node
	{
		Vector3	force;
		Vector3	acceleration;
		Vector3	velocity;
		Vector3	position;
		bool	locked;
	};



	///////////////////////////////////////////////////////////////////////////////////////////////
	struct Spring
	{
		Node*	node1;
		Node*	node2;
		bool	isDiagonal;
	};



	///////////////////////////////////////////////////////////////////////////////////////////////
	class Cloth
	{

	/////////////////////////////////////////////////////////////
	private:

		/////////////////////////////////////////
		// Private member variables
	
		Mesh*			__meshComponent;
		bool			__ready;
		int				__columns;
		int				__rows;
		vector<Node>	__nodes;
		vector<Spring>	__springs;
		float			__dampingCoeff;
		float			__equilibriumDistance;
		float			__nodeMass;
		float			__springCoeff;


		/////////////////////////////////////////
		// Update

		/*
		* Update the nodes and springs based on the passage of dt seconds.
		*/
		void updatePhysics( float dt );

		/*
		* Update the attached mesh component with new vertices and normals.
		*/
		void updateMesh( void );


		/////////////////////////////////////////
		// Springs

		/*
		* Apply the specified force to the node at the specified index.
		*/
		void applySpringForce( int index );

		/*
		* Returns the spring force applied by a spring.
		*/
		Vector3 computeSpringForce( int index );


		/////////////////////////////////////////
		// Dynamic meshing

		/*
		* Set the mesh vertices based on the physics nodes that make up the cloth.
		*/
		void setMeshVertices( void );

		/*
		* Set the mesh normals based on the physics nodes that make up the cloth.
		*/
		void setMeshNormals( void );

		/*
		* Set the mesh UVs based on the physics nodes that make up the cloth.
		*/
		void setMeshUVs( void );
	
	
	/////////////////////////////////////////////////////////////
	public:

		/////////////////////////////////////////
		// ctor and dtor

		Cloth( int rows, int columns, float equilibriumDistance, float nodeMass, float springCoeff, float dampingCoeff );
		Cloth( void );
		~Cloth( void );


		/////////////////////////////////////////
		// Initialization

		/*
		* Set up a cloth with the specified number of rows and columns, spaced apart by the equilibrium distance.
		*/
		void init( int rows, int columns, float equilibriumDistance, float nodeMass, float springCoeff, float dampingCoeff );

		/*
		* Set all values of the cloth to zero and clear the nodes and springs lists.
		*/
		void reset( void );

		/*
		* Create the nodes that make up the cloth.
		*/
		void createNodes( int rows, int columns, int equilibriumDistance );

		/*
		* Create all the springs necessary to connect the cloth together based on the existing nodes.
		*/
		void createSprings( int rows, int columns, vector<Node>& nodes );


		/////////////////////////////////////////
		// Update

		/*
		* Update the nodes and springs based on the passage of dt seconds, then update the mesh.
		*/
		void update( float dt );


		/////////////////////////////////////////
		// Dynamics

		/*
		* Apply the specified force to the node at the specified index.
		*/
		void applyForceToNode( int index, Vector3 force );


		/////////////////////////////////////////
		// Getters

		/*
		* The number of columns of cloth nodes.
		*/
		int columns( void );

		/*
		* The number of rows of cloth nodes.
		*/
		int rows( void );

		/*
		* Returns a reference to the list of nodes in the cloth.
		*/
		vector<Node>& nodes( void );

		/*
		* Returns a reference to the list of springs connecting nodes together in the cloth.
		*/
		vector<Spring>&	springs( void );

		/*
		* Returns the damping coefficient used for the spring interactions.
		*/
		float dampingCoeff( void );

		/*
		* Returns the equilibrium distance used for the spring interactions.
		*/
		float equilibriumDistance( void );

		/*
		* Returns the mass of a single node in the cloth.
		*/
		float nodeMass( void );

		/*
		* Returns the spring coefficient used for the spring interactions.
		*/
		float springCoeff( void );


		/////////////////////////////////////////
		// Setters

		/*
		* Sets the damping coefficient used for the spring interactions.
		*/
		void dampingCoeff( float value );

		/*
		* Sets the equilibrium distance used for the spring interactions.
		*/
		void equilibriumDistance( float value );

		/*
		* Sets the mass of a single node in the cloth.
		*/
		void nodeMass( float value );

		/*
		* Sets the spring coefficient used for the spring interactions.
		*/
		void springCoeff( float value );

	};
}

#endif // APP_CLOTH