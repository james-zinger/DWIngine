#include "DWIngine.h"
#include "Resources.h"
#include "TestApp.h"
#include "GameObject.h"
#include "MeshManager.h"
#include "Scene.h"
#include "Camera.h"
#include <sstream>
//#include "Primitive.h"

#ifndef NULL
#define NULL 0
#endif

using DWI::Vector3;
using DWI::Quaternion;
using DWI::GameObject;
///////////////////////////////////////////////////////////////////////////////////////////////////
// Public 

/////////////////////////////////////////////////////////////////
// ctor and dtor

TestApp::TestApp( void )
{
	__numberOfRenders = 0;
	__maxNumberOfRenders = 10000;
}

TestApp::~TestApp( void )
{
	// No resources to release
}


/////////////////////////////////////////////////////////////////
// Event callback overrides

void TestApp::onStart( void )
{
	__sstream.str( string() );

	GameObject* go = GameObject::Instantiate(
		Vector3( 0, 0, 0 ),
		Quaternion(),
		Vector3( 1, 1, 1 ),
		DWI::DWIngine::singleton()->currentScene()->GetRoot()->getTransformIndex() );



	GameObject* go2 = GameObject::Instantiate(
		Vector3( 0, 0, 0 ),
		Quaternion( ),
		Vector3( 1, 1, 1 ),
		engine( )->currentScene( )->GetRoot( )->getTransformIndex() );

	__sstream << "=============\nResource Test\n=============\n\n";

	// Load a fragment shader from a .FRAGMENTSHADER file
	engine()->resources()->addFragmentShaderFromFile( "Test", "StandardShading.fragmentshader" );
	__sstream << "Fragment Shader (Test): \n\n" << engine()->resources()->getFragmentShader( "Test" )->sourceCode() << "\n===\n\n";

	// Load a mesh from an .OBJ file
	engine()->resources()->addMeshFromObjFile( "M-16", "M16_model.obj", false );
	DWI::MeshAsset* meshAsset = engine()->resources()->getMesh( "M-16" );
	__sstream << "Mesh (M-16): \n\n";
	__sstream << "Vertices: \n\n";
	
	__sstream << "\n===\n\n";

	// Load a texture from a .BMP file
	engine()->resources()->addTextureFromBmpFile( "M-16", "m16.bmp" );
	DWI::TextureAsset* textureAsset = engine()->resources()->getTexture( "M-16" );
	__sstream << "\n===\n\n";

	// Load some text from a .TXT file
	engine()->resources()->addTextFromFile( "Test", "test.txt" );
	__sstream << "Text (Test): \n\n" << engine()->resources()->getText( "Test" )->text() << "\n===\n\n";

	// Load a vertex shader from a .VERTEXSHADER file
	engine()->resources()->addVertexShaderFromFile( "Test", "StandardShading.vertexshader" );
	__sstream << "Vertex Shader (Test): \n\n" << engine()->resources()->getVertexShader( "Test" )->sourceCode() << "\n===\n\n";

	// Create a material from the above shaders and texture
	engine()->resources()->addMaterialFromString( "M-16", "Test", "Test", "M-16" );
	__sstream << "Material (M-16): \n\n";
	DWI::MaterialAsset* materialAsset = engine()->resources()->getMaterial( "M-16" );
	__sstream << "Fragment Shader Name: " << materialAsset->fragmentShaderUniqueName() << "\n";
	__sstream << "Vertex Shader Name: " << materialAsset->vertexShaderUniqueName() << "\n";
	__sstream << "Texture Name: " << materialAsset->textureUniqueName() << "\n";
	__sstream << "\n===\n\n";

	go->addMesh( "M-16", "M-16" );
	

	engine()->trace( __sstream.str() );

	go2->transform();

	go->transform()->Scale = Vector3( 0.5f, 0.5f, 0.5f );
	go->transform()->Rotate( Vector3(0,1,0), 45 );
	go->transform()->Translate( Vector3( 1, 1, 0 ) );

	DWI::Camera* cam = DWI::DWIngine::singleton()->camera();

	cam->setPosition( Vector3( -5, 1, 0 ) );
	engine()->trace( "Starting up..." );
}

void TestApp::onPreRender( void )
{
	//engine()->trace( "PreRender" );
}

void TestApp::onRender( void )
{
	//if ( __numberOfRenders++ > __maxNumberOfRenders )
	//{
	//	engine()->stop();
	//}

	//__sstream.str( string() );
	//__sstream << "Render @ " << engine()->timeSec() << " seconds  ::  Frame rate: " << engine()->fps() << "FPS";
	//engine()->trace( __sstream.str() );

	//engine()->trace( "Render" );
}

void TestApp::onPostRender( void )
{
	//engine()->trace( "PostRender" );
}

void TestApp::onStop( void )
{
	engine()->trace( "Shutting down..." );
}