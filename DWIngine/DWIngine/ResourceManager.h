#ifndef DWI_RESOURCEMANAGER
#define DWI_RESOURCEMANAGER

#include <string>
#include <unordered_map>
#include "Material.h"
#include "MeshData.h"
#include "TextData.h"
#include "TextureData.h"

using std::string;
using std::unordered_map;



namespace DWI
{
	///////////////////////////////////////////////////////////////////////////////////////////////
	class ResourceManager
	{

	/////////////////////////////////////////////////////////////
	private:
		
		/////////////////////////////////////////////
		// Singleton variable

		static ResourceManager* __singleton;
		

		/////////////////////////////////////////////
		// Private member variables

		unordered_map<string, Material>		__materials;
		unordered_map<string, MeshData>		__meshData;
		unordered_map<string, TextData>		__textData;
		unordered_map<string, TextureData>	__textures;


		/////////////////////////////////////////
		// ctor and dtor

		ResourceManager( void );
		~ResourceManager( void );
		


	/////////////////////////////////////////////////////////////////
	public:

		/////////////////////////////////////////////
		// Singleton ctor and dtor

		/**
		* Returns a pointer to the singleton instance of the Resources.
		* @returns Pointer to the HardwareClock instance.
		*/
		static ResourceManager* singleton( void );

		/**
		* Destroys the Resources instance and releases it from heap memory.
		*/
		static void destroySingleton( void );


	};
}

#endif // DWI_RESOURCEMANAGER
