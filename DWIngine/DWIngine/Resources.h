#ifndef DWI_RESOURCES
#define DWI_RESOURCES

#include <string>
#include <unordered_map>
#include "FragmentShaderAsset.h"
#include "MaterialAsset.h"
#include "MeshAsset.h"
#include "TextAsset.h"
#include "TextureAsset.h"
#include "VertexShaderAsset.h"

using std::string;
using std::unordered_map;



namespace DWI
{
	// Type Definitions
	typedef unordered_map<string, FragmentShaderAsset*> FragmentShaderRegistry;
	typedef unordered_map<string, MaterialAsset*> MaterialRegistry;
	typedef unordered_map<string, MeshAsset*> MeshRegistry;
	typedef unordered_map<string, TextAsset*> TextRegistry;
	typedef unordered_map<string, TextureAsset*> TextureRegistry;
	typedef unordered_map<string, VertexShaderAsset*> VertexShaderRegistry;


	///////////////////////////////////////////////////////////////////////////////////////////////
	class Resources
	{

	/////////////////////////////////////////////////////////////
	private:
		
		/////////////////////////////////////////////
		// Singleton variable

		static Resources* __singleton;
		

		/////////////////////////////////////////////
		// Private member variables

		FragmentShaderRegistry	__fragmentShaders;
		MaterialRegistry		__materials;
		MeshRegistry			__meshes;
		TextRegistry			__text;
		TextureRegistry			__textures;
		VertexShaderRegistry	__vertexShaders;


		/////////////////////////////////////////
		// ctor and dtor

		Resources( void );
		~Resources( void );
		


	/////////////////////////////////////////////////////////////////
	public:

		/////////////////////////////////////////////
		// Singleton ctor and dtor

		/**
		* Returns a pointer to the singleton instance of the Resources.
		* @returns Pointer to the Time instance.
		*/
		static Resources* singleton( void );

		/**
		* Destroys the Resources instance and releases it from heap memory.
		*/
		static void destroySingleton( void );


		/////////////////////////////////////////////
		// Static Helpers

		/*
		* Loads the .OBJ file at filepath into the provided MeshAsset instance.
		* @returns Whether or not the file could be read successfully.
		*/
		static void loadMeshFromObjFile( string filepath, MeshAsset* out );

		/*
		* Loads the fragment shader file at filepath into the provided FragmentShaderAsset instance.
		* @returns Whether or not the file could be read successfully.
		*/
		static void loadFragmentShaderFromFile( string filepath, FragmentShaderAsset* out );

		/*
		* Loads the material file at filepath into the provided MaterialAsset instance.
		* @returns Whether or not the file could be read successfully.
		*/
		static void loadMaterialFromFile( string filepath, MaterialAsset* out );

		/*
		* Loads the text file at filepath into the provided TextAsset instance.
		* @returns Whether or not the file could be read successfully.
		*/
		static void loadTextFromFile( string filepath, TextAsset* out );

		/*
		* Loads the .BMP file at filepath into the provided TextureAsset instance.
		* @returns Whether or not the file could be read successfully.
		*/
		static void loadTextureFromBmpFile( string filepath, TextureAsset* out );

		/*
		* Loads the .TGA file at filepath into the provided TextureAsset instance.
		* @returns Whether or not the file could be read successfully.
		*/
		static void loadTextureFromTgaFile( string filepath, TextureAsset* out );

		/*
		* Loads the vertex shader file at filepath into the provided VertexShaderAsset instance.
		* @returns Whether or not the file could be read successfully.
		*/
		static void loadVertexShaderFromFile( string filepath, VertexShaderAsset* out );

		/*
		* Reads a plain text file in as a string.
		* @returns Whether or not the file could be read successfully.
		*/
		static void readPlainTextFile( string filepath, string* out );




		/////////////////////////////////////////////
		// Fragment Shaders

		/*
		* Adds the provided FragmentShaderAsset to the fragment shader registry, identified by the name uniqueName.
		* @returns Whether or not the new entry was added to the registry.
		*/
		bool addFragmentShader( string uniqueName, FragmentShaderAsset* fragmentShaderAsset );

		/*
		* Creates a FragmentShaderAsset from the provided string and adds it to the fragment shader 
		* registry, identified by the name uniqueName.
		* @returns Whether or not the new entry was added to the registry.
		*/
		bool addFragmentShaderFromString( string uniqueName, string fragmentShaderString );

		/*
		* Creates a FragmentShaderAsset from the file at the provided filepath and adds it to the fragment shader 
		* registry, identified by the name uniqueName.
		* @returns Whether or not the new entry was added to the registry.
		*/
		bool addFragmentShaderFromFile( string uniqueName, string fragmentShaderFilepath );

		/*
		* Gets the fragment shader stored at uniqueName in the fragment shader registry.
		* @returns A FragmentShaderAsset instance representing this fragment shader (NULL if none is found).
		*/
		FragmentShaderAsset* getFragmentShader( string uniqueName );

		/*
		* Gets an iterator pointing to a fragment shader, that is guaranteed to iterate over each fragment 
		* shader in the fragment shader registry at least once.
		* @returns An iterator pointing to a random fragment shader.
		*/
		FragmentShaderRegistry::iterator getFragmentShaderIterator();

		/*
		* Removes the fragment shader stored at uniqueName in the fragment shader registry.
		*/
		void removeFragmentShader( string uniqueName );


		/////////////////////////////////////////////
		// Materials

		/*
		* Adds the provided MaterialAsset to the material registry, identified by the name uniqueName.
		* @returns Whether or not the new entry was added to the registry.
		*/
		bool addMaterial( string uniqueName, MaterialAsset* materialAsset );

		/*
		* Creates a MaterialAsset from the provided strings and adds it to the material registry, 
		* identified by the name uniqueName.
		* @returns Whether or not the new entry was added to the registry.
		*/
		bool addMaterialFromString( string uniqueName, string fragmentShaderName, string vertexShaderName, string textureName );

		/*
		* Creates a MaterialAsset from the file at the provided filepath and adds it to the material 
		* registry, identified by the name uniqueName.
		* @returns Whether or not the new entry was added to the registry.
		*/
		bool addMaterialFromFile( string uniqueName, string materialFilepath );

		/*
		* Gets the material stored at uniqueName in the material registry.
		* @returns A MaterialAsset instance representing this material (NULL if none is found).
		*/
		MaterialAsset* getMaterial( string uniqueName );

		/*
		* Gets an iterator pointing to a material, that is guaranteed to iterate over each material
		* in the material registry at least once.
		* @returns An iterator pointing to a random material.
		*/
		MaterialRegistry::iterator getMaterialIterator();
		
		/*
		* Removes the material stored at uniqueName in the material registry.
		*/
		void removeMaterial( string uniqueName );


		/////////////////////////////////////////////
		// Meshes

		/*
		* Adds the provided MeshAsset to the mesh registry, identified by the name uniqueName.
		* @returns Whether or not the new entry was added to the registry.
		*/
		bool addMesh( string uniqueName, MeshAsset* meshAsset );

		/*
		* Creates a MeshAsset from the .OBJ file at the provided filepath and adds it to the mesh 
		* registry, identified by the name uniqueName.
		* @returns Whether or not the new entry was added to the registry.
		*/
		bool addMeshFromObjFile( string uniqueName, string meshFilepath );

		/*
		* Gets the mesh stored at uniqueName in the mesh registry.
		* @returns A MeshAsset instance representing this mesh (NULL if none is found).
		*/
		MeshAsset* getMesh( string uniqueName );

		/*
		* Gets an iterator pointing to a mesh, that is guaranteed to iterate over each mesh
		* in the mesh registry at least once.
		* @returns An iterator pointing to a random mesh.
		*/
		MeshRegistry::iterator getMeshIterator();
		
		/*
		* Removes the mesh stored at uniqueName in the mesh registry.
		*/
		void removeMesh( string uniqueName );
		
		
		/////////////////////////////////////////////
		// Text

		/*
		* Adds the provided TextAsset to the text registry, identified by the name uniqueName.
		* @returns Whether or not the new entry was added to the registry.
		*/
		bool addText( string uniqueName, TextAsset* textAsset );

		/*
		* Creates a TextAsset from the provided string and adds it to the text 
		* registry, identified by the name uniqueName.
		* @returns Whether or not the new entry was added to the registry.
		*/
		bool addTextFromString( string uniqueName, string textString );

		/*
		* Creates a TextAsset from the file at the provided filepath and adds it to the text
		* registry, identified by the name uniqueName.
		* @returns Whether or not the new entry was added to the registry.
		*/
		bool addTextFromFile( string uniqueName, string textFilepath );

		/*
		* Gets the text stored at uniqueName in the text registry.
		* @returns A TextAsset instance representing this text (NULL if none is found).
		*/
		TextAsset* getText( string uniqueName );

		/*
		* Gets an iterator pointing to a text, that is guaranteed to iterate over each text
		* in the text registry at least once.
		* @returns An iterator pointing to a random text.
		*/
		TextRegistry::iterator getTextIterator();
		
		/*
		* Removes the text stored at uniqueName in the text registry.
		*/
		void removeText( string uniqueName );


		/////////////////////////////////////////////
		// Textures

		/*
		* Adds the provided TextureAsset to the texture registry, identified by the name uniqueName.
		* @returns Whether or not the new entry was added to the registry.
		*/
		bool addTexture( string uniqueName, TextureAsset* textureAsset );

		/*
		* Creates a TextureAsset from the .BMP file at the provided filepath and adds it to the texture 
		* registry, identified by the name uniqueName.
		* @returns Whether or not the new entry was added to the registry.
		*/
		bool addTextureFromBmpFile( string uniqueName, string textureFilepath );

		/*
		* Creates a TextureAsset from the .TGA file at the provided filepath and adds it to the texture 
		* registry, identified by the name uniqueName.
		* @returns Whether or not the new entry was added to the registry.
		*/
		bool addTextureFromTgaFile( string uniqueName, string textureFilepath );

		/*
		* Gets the texture stored at uniqueName in the texture registry.
		* @returns A TextureAsset instance representing this texture (NULL if none is found).
		*/
		TextureAsset* getTexture( string uniqueName );
		
		/*
		* Gets an iterator pointing to a texture, that is guaranteed to iterate over each texture
		* in the texture registry at least once.
		* @returns An iterator pointing to a random texture.
		*/
		TextureRegistry::iterator getTextureIterator();

		/*
		* Removes the texture stored at uniqueName in the texture registry.
		*/
		void removeTexture( string uniqueName );


		/////////////////////////////////////////////
		// Vertex Shaders

		/*
		* Adds the provided VertexShaderAsset to the vertex shader registry, identified by the name uniqueName.
		* @returns Whether or not the new entry was added to the registry.
		*/
		bool addVertexShader( string uniqueName, VertexShaderAsset* vertexShaderAsset );

		/*
		* Creates a VertexShaderAsset from the provided string and adds it to the vertex shader 
		* registry, identified by the name uniqueName.
		* @returns Whether or not the new entry was added to the registry.
		*/
		bool addVertexShaderFromString( string uniqueName, string vertexShaderString );

		/*
		* Creates a VertexShaderAsset from the file at the provided filepath and adds it to the vertex shader 
		* registry, identified by the name uniqueName.
		* @returns Whether or not the new entry was added to the registry.
		*/
		bool addVertexShaderFromFile( string uniqueName, string vertexShaderFilepath );
		
		/*
		* Gets the vertex shader stored at uniqueName in the vertex shader registry.
		* @returns A VertexShaderAsset instance representing this vertex shader (NULL if none is found).
		*/
		VertexShaderAsset* getVertexShader( string uniqueName );

		/*
		* Gets an iterator pointing to a vertex shader, that is guaranteed to iterate over each vertex
		* shader in the vertex shader registry at least once.
		* @returns An iterator pointing to a random vertex shader.
		*/
		VertexShaderRegistry::iterator getVertexShaderIterator();
		
		/*
		* Removes the vertex shader stored at uniqueName in the vertex shader registry.
		*/
		void removeVertexShader( string uniqueName );
	};
}

#endif // DWI_RESOURCES
