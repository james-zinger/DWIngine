#ifndef DWI_CAMERA
#define DWI_CAMERA
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
using glm::vec3;
using glm::mat4;
using glm::perspective;
using glm::lookAt;
namespace DWI
{
	class Camera
	{
	private:

		

		///////////////////////////////
		// private members
		mat4 Proj;
		mat4 View;
		bool ProjDirty;
		bool ViewDirty;

		///////////////////////////////
		// private view members
		vec3 Position;
		vec3 LookAt;
		vec3 UpVector;

		///////////////////////////////
		// private projection members
		float FoVy;
		float aspectRatio;
		float zNear;
		float zFar;

	public:
		///////////////////////////////
		// ctor and dtor
		Camera( vec3& Position, vec3& LookAt, vec3& UpVector, float FoVy, float aspectRatio, float zNear, float zFar );
		Camera(void);
		~Camera(void);

		///////////////////////////////
		// public Helper Functions
		void Update( void );

		///////////////////////////////
		// public projection setters
		void setFoVy( float FoVy );
		void setAspectRatio( float aspectRatio );
		void setZNear( float zNear );
		void setZFar ( float zFar );

		///////////////////////////////
		// public view setters
		void setPosition( vec3 Position );
		void setLookAt( vec3 LookAt );
		void setUpVector( vec3 UpVector );

		///////////////////////////////
		// public projection getters
		float getFoVy( void );
		float getAspectRatio( void );
		float getZNear( void );
		float getZFar( void );
		
		///////////////////////////////
		// public view getters
		vec3 getPosition( void );
		vec3 getLookAt( void );
		vec3 getUpVector( void );

		///////////////////////////////
		// public matrix getters
		mat4 getView( void );
		mat4 getProj( void );
	};
}

#endif //DWI_CAMERA