#include <fstream>
#include <sstream>
#include "FileCouldNotBeOpenedException.h"
#include "Log.h"
#include "Resources.h"

#ifndef NULL
#define NULL 0
#endif

using std::ifstream;
using std::out_of_range;
using std::pair;
using std::string;
using std::stringstream;
using std::vector;



///////////////////////////////////////////////////////////////////////////////////////////////////
// Private

/////////////////////////////////////////////////////////////////
// Singleton variable

DWI::Resources* DWI::Resources::__singleton = NULL;


/////////////////////////////////////////////////////////////////
// ctor and dtor

DWI::Resources::Resources( void )
{

}

DWI::Resources::~Resources( void )
{
	__fragmentShaders.clear();
	__materials.clear();
	__meshes.clear();
	__text.clear();
	__textures.clear();
	__vertexShaders.clear();
}



///////////////////////////////////////////////////////////////////////////////////////////////////
// Public

/////////////////////////////////////////////////////////////////
// Singleton ctor and dtor

DWI::Resources* DWI::Resources::singleton( void )
{
	if ( __singleton == NULL )
	{
		__singleton = new Resources();
	}

	return __singleton;
}

void DWI::Resources::destroySingleton( void )
{
	if ( __singleton != NULL )
	{
		delete __singleton;
		__singleton = NULL;
	}
}


/////////////////////////////////////////////////////////////////
// Static Helpers

void DWI::Resources::loadMeshFromObjFile( const string filepath, MeshAsset* out )
{
	vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	vector<Vector3> temp_vertices; 
	vector<Vector2> temp_uvs;
	vector<Vector3> temp_normals;


	FILE* file = fopen( filepath.c_str(), "r" );
	if( file == NULL )
	{
		//printf( "Impossible to open the file ! Are you in the right path ? See Tutorial 1 for details\n" );
		throw new FileCouldNotBeOpenedException( "Resources >> .OBJ file header is corrupted!" );
	}

	while( true ) // Yeah, it sucks but I didn't write it and it works so I'm leaving it alone
	{
		char lineHeader[ 128 ];

		// read the first word of the line
		int res = fscanf( file, "%s", lineHeader );
		if ( res == EOF )
		{
			break; // EOF = End Of File. Quit the loop.
		}
		
		if ( strcmp( lineHeader, "v" ) == 0 )
		{
			glm::vec3 vertex;
			fscanf( file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
			temp_vertices.push_back( vertex );
		}
		else if ( strcmp( lineHeader, "vt" ) == 0 )
		{
			glm::vec2 uv;
			fscanf( file, "%f %f\n", &uv.x, &uv.y );
			uv.y = uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
			temp_uvs.push_back( uv );
		}
		else if ( strcmp( lineHeader, "vn" ) == 0 )
		{
			glm::vec3 normal;
			fscanf( file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
			temp_normals.push_back( normal );
		}
		else if ( strcmp( lineHeader, "f" ) == 0 )
		{
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[ 3 ], uvIndex[ 3 ], normalIndex[ 3 ];
			int matches = fscanf( file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", 
				&vertexIndex[ 0 ], &uvIndex[ 0 ], &normalIndex[ 0 ], 
				&vertexIndex[ 1 ], &uvIndex[ 1 ], &normalIndex[ 1 ], 
				&vertexIndex[ 2 ], &uvIndex[ 2 ], &normalIndex[ 2 ] 
			);

			if ( matches != 9 )
			{
				//printf("File can't be read by our simple parser :-( Try exporting with other options\n");
				throw new FileCouldNotBeOpenedException( "Resources >> .OBJ file format is broken! try exporting with different settings." );
			}

			vertexIndices.push_back( vertexIndex[ 0 ] );
			vertexIndices.push_back( vertexIndex[ 1 ] );
			vertexIndices.push_back( vertexIndex[ 2 ] );

			uvIndices.push_back( uvIndex[ 0 ] );
			uvIndices.push_back( uvIndex[ 1 ] );
			uvIndices.push_back( uvIndex[ 2 ] );

			normalIndices.push_back( normalIndex[ 0 ] );
			normalIndices.push_back( normalIndex[ 1 ] );
			normalIndices.push_back( normalIndex[ 2 ] );
		}
		else
		{
			// Probably a comment, eat up the rest of the line
			char stupidBuffer[ 1000 ];
			fgets( stupidBuffer, 1000, file );
		}
	}

	// Clear the mesh
	out->vertices().clear();
	out->normals().clear();
	out->uvs().clear();

	// For each vertex of each triangle
	for ( unsigned int i = 0; i < vertexIndices.size(); i++ )
	{
		// Get the indices of its attributes
		unsigned int vertexIndex = vertexIndices[ i ];
		unsigned int uvIndex = uvIndices[ i ];
		unsigned int normalIndex = normalIndices[ i ];
		
		// Get the attributes thanks to the index
		Vector3 vertex = temp_vertices[ vertexIndex - 1 ];
		Vector2 uv = temp_uvs[ uvIndex - 1 ];
		Vector3 normal = temp_normals[ normalIndex - 1 ];
		
		// Put the attributes in buffers
		out->vertices().push_back( vertex );
		out->uvs().push_back( uv );
		out->normals().push_back( normal );
	}
}

void DWI::Resources::loadFragmentShaderFromFile( const string filepath, FragmentShaderAsset* out )
{
	try
	{
		string fileContents = "";
		Resources::readPlainTextFile( filepath, &fileContents );
		out->sourceCode( fileContents );
	}
	catch ( FileCouldNotBeOpenedException* e )
	{
		stringstream sstream;
		sstream << "Opening " << filepath << " for read has failed!";
		Log::LogError( sstream.str() );
		delete e;
	}
}

void DWI::Resources::loadMaterialFromFile( const string filepath, MaterialAsset* out )
{
	// Not yet implemented
}

void DWI::Resources::loadTextFromFile( const string filepath, TextAsset* out )
{
	try
	{
		string fileContents = "";
		Resources::readPlainTextFile( filepath, &fileContents );
		out->text( fileContents );
	}
	catch ( FileCouldNotBeOpenedException* e )
	{
		stringstream sstream;
		sstream << "Opening " << filepath << " for read has failed!";
		Log::LogError( sstream.str() );
		delete e;
	}
}

void DWI::Resources::loadTextureFromBmpFile( const string filepath, TextureAsset* out )
{
	// Data read from the header of the BMP file
	unsigned char header[54];
	unsigned int dataPos;
	unsigned int imageSize;
	unsigned int width, height;

	// Actual RGB data
	unsigned char* data;

	// Open the file
	FILE* file = fopen( filepath.c_str(), "rb" );
	if ( !file )
	{
		//printf( "%s could not be opened. Are you in the right directory ? Don't forget to read the FAQ !\n", filepath );
		getchar();
		throw new FileCouldNotBeOpenedException( "Resources >> .BMP file could not be opened!" );
	}

	// Read the header, i.e. the 54 first bytes

	// If less than 54 bytes are read, problem
	if ( fread( header, 1, 54, file ) != 54 )
	{ 
		throw new FileCouldNotBeOpenedException( "Resources >> .BMP file header is corrupted!" );
	}

	// A BMP files always begins with "BM"
	if ( header[ 0 ] != 'B' || header[ 1 ] != 'M' )
	{
		throw new FileCouldNotBeOpenedException( "Resources >> .BMP file header is corrupted!" );
	}

	// Make sure this is a 24bpp file
	if ( *(int*)&( header[ 0x1E ] ) !=  0 )
	{
		throw new FileCouldNotBeOpenedException( "Resources >> .BMP file header is corrupted!" );
	}
	if ( *(int*)&( header[ 0x1C ] ) != 24 )
	{
		throw new FileCouldNotBeOpenedException( "Resources >> .BMP file header is corrupted!" );
	}

	// Read the information about the image
	dataPos    = *(int*)&( header[ 0x0A ] );
	imageSize  = *(int*)&( header[ 0x22 ] );
	width      = *(int*)&( header[ 0x12 ] );
	height     = *(int*)&( header[ 0x16 ] );

	// Some BMP files are misformatted, guess missing information
	if ( imageSize == 0 ) imageSize = width * height * 3; // 3 : one byte for each Red, Green and Blue component
	if ( dataPos == 0 ) dataPos = 54; // The BMP header is done that way

	// Create a buffer
	data = new unsigned char[ imageSize ];

	// Read the actual data from the file into the buffer
	fread( data, 1, imageSize, file );

	// Everything is in memory now, the file wan be closed
	fclose ( file );

	// Assign the image data to the texture
	out->imageData( data );
}

void DWI::Resources::loadTextureFromTgaFile( const string filepath, TextureAsset* out )
{
	// Not yet implemented
}

void DWI::Resources::loadVertexShaderFromFile( const string filepath, VertexShaderAsset* out )
{
	try
	{
		string fileContents = "";
		Resources::readPlainTextFile( filepath, &fileContents );
		out->sourceCode( fileContents );
	}
	catch ( FileCouldNotBeOpenedException* e )
	{
		stringstream sstream;
		sstream << "Opening " << filepath << " for read has failed!";
		Log::LogError( sstream.str() );
		delete e;
	}
}

void DWI::Resources::readPlainTextFile( const string filepath, string* out )
{
	stringstream sstream;
	ifstream fileStream( filepath, std::ios::in );
	if ( fileStream.is_open() )
	{
		throw new FileCouldNotBeOpenedException( "Resources >> Text file could not be opened!" );
	}
	string line = "";
	while ( getline( fileStream, line ) )
	{
		sstream << line << "\n";
	}
	fileStream.close();
}


/////////////////////////////////////////////////////////////////
// Fragment Shaders

bool DWI::Resources::addFragmentShader( const string uniqueName, FragmentShaderAsset* fragmentShaderAsset )
{
	pair<unordered_map<string, FragmentShaderAsset>::iterator, bool> result = 
		__fragmentShaders.emplace( uniqueName, *fragmentShaderAsset );
	return result.second;
}

bool DWI::Resources::addFragmentShaderFromString( const string uniqueName, const string fragmentShaderString )
{
	FragmentShaderAsset* asset = new FragmentShaderAsset( uniqueName, fragmentShaderString );
	return addFragmentShader( uniqueName, asset );
}

bool DWI::Resources::addFragmentShaderFromFile( const string uniqueName, const string fragmentShaderFilepath )
{
	FragmentShaderAsset* asset = new FragmentShaderAsset( uniqueName );
	Resources::loadFragmentShaderFromFile( fragmentShaderFilepath, asset );
	return addFragmentShader( uniqueName, asset );
}

DWI::FragmentShaderAsset* DWI::Resources::getFragmentShader( const string uniqueName )
{
	try
	{
		return &__fragmentShaders.at( uniqueName );
	}
	catch ( const std::out_of_range& e )
	{
		return NULL;
	}
}

unordered_map<string, DWI::FragmentShaderAsset>::iterator DWI::Resources::getFragmentShaderIterator()
{
	return __fragmentShaders.begin();
}

void DWI::Resources::removeFragmentShader( const string uniqueName )
{
	__fragmentShaders.erase( uniqueName );
}


/////////////////////////////////////////////////////////////////
// Materials

bool DWI::Resources::addMaterial( const string uniqueName, MaterialAsset* materialAsset )
{
	pair<unordered_map<string, MaterialAsset>::iterator, bool> result = 
		__materials.emplace( uniqueName, *materialAsset );
	return result.second;
}

bool DWI::Resources::addMaterialFromFile( const string uniqueName, const string materialFilepath )
{
	// Not yet implemented
	return false;
}

DWI::MaterialAsset* DWI::Resources::getMaterial( const string uniqueName )
{
	try
	{
		return &__materials.at( uniqueName );
	}
	catch ( const std::out_of_range& e )
	{
		return NULL;
	}
}

unordered_map<string, DWI::MaterialAsset>::iterator DWI::Resources::getMaterialIterator()
{
	return __materials.begin();
}

void DWI::Resources::removeMaterial( const string uniqueName )
{
	__materials.erase( uniqueName );
}


/////////////////////////////////////////////////////////////////
// Meshes

bool DWI::Resources::addMesh( const string uniqueName, MeshAsset* meshAsset )
{
	pair<unordered_map<string, MeshAsset>::iterator, bool> result = 
		__meshes.emplace( uniqueName, *meshAsset );
	return result.second;
}

bool DWI::Resources::addMeshFromObjFile( const string uniqueName, const string meshFilepath )
{
	MeshAsset* asset = new MeshAsset( uniqueName );
	Resources::loadMeshFromObjFile( meshFilepath, asset );
	return addMesh( uniqueName, asset );
}

DWI::MeshAsset* DWI::Resources::getMesh( const string uniqueName )
{
	try
	{
		return &__meshes.at( uniqueName );
	}
	catch ( const std::out_of_range& e )
	{
		return NULL;
	}
}

unordered_map<string, DWI::MeshAsset>::iterator DWI::Resources::getMeshIterator()
{
	return __meshes.begin();
}

void DWI::Resources::removeMesh( const string uniqueName )
{
	__meshes.erase( uniqueName );
}
		
		
/////////////////////////////////////////////////////////////////
// Text

bool DWI::Resources::addText( const string uniqueName, TextAsset* textAsset )
{
	pair<unordered_map<string, TextAsset>::iterator, bool> result = 
		__text.emplace( uniqueName, *textAsset );
	return result.second;
}

bool DWI::Resources::addTextFromString( const string uniqueName, const string textString )
{
	TextAsset* asset = new TextAsset( uniqueName, textString );
	return addText( uniqueName, asset );
}

bool DWI::Resources::addTextFromFile( const string uniqueName, const string textFilepath )
{
	TextAsset* asset = new TextAsset( uniqueName );
	Resources::loadTextFromFile( textFilepath, asset );
	return addText( uniqueName, asset );
}

DWI::TextAsset* DWI::Resources::getText( const string uniqueName )
{
	try
	{
		return &__text.at( uniqueName );
	}
	catch ( const std::out_of_range& e )
	{
		return NULL;
	}
}

unordered_map<string, DWI::TextAsset>::iterator DWI::Resources::getTextIterator()
{
	return __text.begin();
}

void DWI::Resources::removeText( const string uniqueName )
{
	__text.erase( uniqueName );
}


/////////////////////////////////////////////////////////////////
// Textures

bool DWI::Resources::addTexture( const string uniqueName, TextureAsset* textureAsset )
{
	pair<unordered_map<string, TextureAsset>::iterator, bool> result = 
		__textures.emplace( uniqueName, *textureAsset );
	return result.second;
}

bool DWI::Resources::addTextureFromBmpFile( const string uniqueName, const string textureFilepath )
{
	TextureAsset* asset = new TextureAsset( uniqueName );
	Resources::loadTextureFromBmpFile( textureFilepath, asset );
	return addTexture( uniqueName, asset );
}

bool DWI::Resources::addTextureFromTgaFile( const string uniqueName, const string textureFilepath )
{
	// Not yet implemented
	return false;
}

DWI::TextureAsset* DWI::Resources::getTexture( const string uniqueName )
{
	try
	{
		return &__textures.at( uniqueName );
	}
	catch ( const std::out_of_range& e )
	{
		return NULL;
	}
}

unordered_map<string, DWI::TextureAsset>::iterator DWI::Resources::getTextureIterator()
{
	return __textures.begin();
}

void DWI::Resources::removeTexture( const string uniqueName )
{
	__textures.erase( uniqueName );
}


/////////////////////////////////////////////////////////////////
// Vertex Shaders

bool DWI::Resources::addVertexShader( const string uniqueName, VertexShaderAsset* vertexShaderAsset )
{
	pair<unordered_map<string, VertexShaderAsset>::iterator, bool> result = 
		__vertexShaders.emplace( uniqueName, *vertexShaderAsset );
	return result.second;
}

bool DWI::Resources::addVertexShaderFromString( const string uniqueName, const string vertexShaderString )
{
	VertexShaderAsset* asset = new VertexShaderAsset( uniqueName, vertexShaderString );
	return addVertexShader( uniqueName, asset );
}

bool DWI::Resources::addVertexShaderFromFile( const string uniqueName, const string vertexShaderFilepath )
{
	VertexShaderAsset* asset = new VertexShaderAsset( uniqueName );
	Resources::loadVertexShaderFromFile( vertexShaderFilepath, asset );
	return addVertexShader( uniqueName, asset );
}

DWI::VertexShaderAsset* DWI::Resources::getVertexShader( const string uniqueName )
{
	try
	{
		return &__vertexShaders.at( uniqueName );
	}
	catch ( const std::out_of_range& e )
	{
		return NULL;
	}
}

unordered_map<string, DWI::VertexShaderAsset>::iterator DWI::Resources::getVertexShaderIterator()
{
	return __vertexShaders.begin();
}

void DWI::Resources::removeVertexShader( const string uniqueName )
{
	__vertexShaders.erase( uniqueName );
}
