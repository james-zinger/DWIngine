#pragma once


#include "Model.h"
#include "Primitive.h"
#include <vector>
class AbstractRenderer
{
protected:
	int __screenWidth;
	int __screenHeight;
	std::vector<Primitive> __primitives;
	std::vector<Model> __models;

	//Render Functions
	virtual void renderMesh(Model& model) = 0; 

	virtual void renderPrimitive(Primitive& primitive) = 0;

public:


	//Ctor and Dtor
	AbstractRenderer(void);
	~AbstractRenderer(void);

	virtual void RenderScene(void) = 0;

	virtual void AddPrimitive(Primitive& primitive) = 0;
	
};

