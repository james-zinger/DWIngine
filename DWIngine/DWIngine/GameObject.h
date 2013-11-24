#ifndef DWI_GAMEOBJECT
#define DWI_GAMEOBJECT

#include <list>
#include <string>
#include "Transform.h"
#include "Resources.h"

using std::string;
using std::list;

namespace DWI
{
	///////////////////////////////////////////////////////////////////////////////////////////////
	class GameObject
	{

		friend class Scene;
		/////////////////////////////////////////////////////////////
	private:

		/**
		 * Default constructor.
		 */
		GameObject( void );

		static list<GameObject*>* __gameObjects;

		bool isEnabled;

		int __transform;

		int __mesh;


		/////////////////////////////////////////////////////////////
	public:

		/**
		* Destructor.
		*/
		virtual ~GameObject( void );

		//////////////////////////////////////
		// public member variables

		string name;

		/**
		 * @fn	int GameObject::getTransformIndex( void );
		 * @brief	public functions.
		 * @return	The transform index.
		 */
		int getTransformIndex( void );

		/**
		 * @fn	int GameObject::getMeshIndex( void );
		 * @brief	Gets mesh index.
		 * @return	The mesh index.
		 */
		int getMeshIndex( void );

		/**
		 * @fn	void GameObject::addMesh( string meshAsset, string materialAsset );
		 * @brief	adds the mesh component to the gameobject
		 * @param	meshAsset	 	The mesh asset.
		 * @param	materialAsset	The material asset.
		 */
		void addMesh( string meshAsset, string materialAsset );

		/**
		 * @fn	void GameObject::addCloth( void );
		 * @brief	adds the cloth component to the gameobject
		 */
		void addCloth( void );

		/**
		 * @fn	Transform* GameObject::transform(void );
		 * @brief	Gets the transform.
		 * @return	null if it fails, else a Transform*.
		 */
		Transform* transform( void );

		//////////////////////////////////////
		// public Static functions and members

		/**
		 * @fn	static list<GameObject*>* GameObject::GameObjectsList( void );
		 * @brief	Game objects list.
		 * @return	null if it fails, else a list&lt;GameObject*&gt;*.
		 */
		static list<GameObject*>* GameObjectsList( void );

		/**
		 * @fn	static GameObject* GameObject::Instantiate( Vector3& Position, Quaternion& Orientation,
		 * 		Vector3& Scale, int parent );
		 * @brief	Instantiates.
		 * @param [in,out]	Position   	The position.
		 * @param [in,out]	Orientation	The orientation.
		 * @param [in,out]	Scale	   	The scale.
		 * @param	parent			   	The parent transform.
		 * @return	null if it fails, else a GameObject*.
		 */
		static GameObject* Instantiate( Vector3& Position, Quaternion& Orientation, Vector3& Scale, int parent );

	};
}

#endif // DWI_GAMEOBJECT
