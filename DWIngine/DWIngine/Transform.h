#ifndef DWI_TRANSFORM
#define DWI_TRANSFORM

#include "Component.h"
#include "DWMath.h"
#include <vector>

using std::vector;

namespace DWI
{
	///////////////////////////////////////////////////////////////////////////////////////////////
	class Transform : public Component
	{

		// The SceneManager manages all Transforms in the scene. Look to this class for functionality for
		// instantiation and destruction of Transforms and any other sensitive process.
		// friend class scene;
		friend class TransformManager;

		/////////////////////////////////////////////////////////////////
	private:

		/////////////////////////////////////////////
		// Private member variables
		
		int			__parent;
		vector<int>	__children;
		/**
		 * @fn	Transform::Transform( const unsigned int uniqueID, GameObject* gameObject );
		 * @brief	Constructor.
		 * @param	uniqueID		  	Unique identifier.
		 * @param [in,out]	gameObject	If non-null, the game object.
		 */
		Transform( const unsigned int uniqueID, GameObject* gameObject );

		
		/////////////////////////////////////////////////////////////////
	public:

		virtual ~Transform( void );

		/////////////////////////////////////////////
		// public member variables
		Vector3			Position;
		Quaternion		Orientation;
		Vector3			Scale;

		/**
		 * @fn	void Transform::AddChild( TransformKey Child );
		 * @brief	Adds a child.
		 * @param	Child	The child's Key.
		 */
		void	AddChild( int Child );

		/**
		 * @fn	bool Transform::RemoveChild( TransformKey Child );
		 * @brief	Removes the child described by TransformKey Child.
		 * @param	Child	The child.
		 * @return	true if it succeeds, false if it fails.
		 */
		bool	RemoveChild( int Child );

#pragma region Public Getters And Setters

		/**
		 * @fn	Vector3* Transform::GetPosition( void );
		 * @brief	Gets the position.
		 * @return	null if it fails, else the position.
		 */
		Vector3*		GetPosition( void );

		/**
		 * @fn	Quaternion* Transform::GetOrientation( void );
		 * @brief	Gets the orientation.
		 * @return	null if it fails, else the orientation.
		 */
		Quaternion*		GetOrientation( void );

		/**
		 * @fn	Vector3* Transform::GetScale( void );
		 * @brief	Gets the scale.
		 * @return	null if it fails, else the scale.
		 */
		Vector3*		GetScale( void );

		/**
		 * @fn	TransformKey Transform::GetParent( void );
		 * @brief	Gets the parent of this item.
		 * @return	null if it fails, else the parent.
		 */
		int		GetParent( void );

		/**
		 * @fn	void Transform::SetPosition( Vector3* position );
		 * @brief	Sets the position.
		 * @param [in,out]	position	The position of the transform.
		 */
		void			SetPosition( Vector3* position );

		/**
		 * @fn	void Transform::SetOrientation( Quaternion* quat );
		 * @brief	Sets the orientation.
		 * @param [in,out]	quat	The quaternion for the orientation of the transform.
		 */
		void			SetOrientation( Quaternion* quat );

		/**
		 * @fn	void Transform::SetScale( Vector3* scale );
		 * @brief	Sets the scale.
		 * @param [in,out]	scale	The scale of the transform.
		 */
		void			SetScale( Vector3* scale );

		/**
		 * @fn	void Transform::SetParent( TransformKey parent );
		 * @brief	Sets a parent.
		 * @param	parent	If non-null, the parent.
		 */
		void			SetParent( int parent );

#pragma endregion


	};
}

#endif // DWI_TRANSFORM
