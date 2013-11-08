#include "Camera.h"

using DWI::Camera;

Camera::Camera( vec3& Position, vec3& LookAt, vec3& UpVector, float FoVy, float aspectRatio, float zNear, float zFar )
{
	this->Position = Position;
	this->LookAt = LookAt;
	this->UpVector = UpVector;
	this->FoVy = FoVy;
	this->aspectRatio = aspectRatio;
	this->zNear = zNear;
	this->zFar = zFar;

	Proj = perspective(FoVy, aspectRatio, zNear, zFar);
	View = lookAt(Position, LookAt, UpVector);

	ProjDirty = false;
	ViewDirty = false;
}

Camera::Camera(void)
{
	Camera( vec3(0,0,-10),
			vec3(0,0,0),
			vec3(0,1,0),
			45.0f,
			4.0f/3.0f,
			0.1f,
			1000.0f);
}

Camera::~Camera(void)
{

}

void Camera::Update( void )
{
	if ( ProjDirty )
	{
		Proj = perspective(FoVy, aspectRatio, zNear, zFar);
		ProjDirty = false;
	}

	if ( ViewDirty )
	{
		View = lookAt( Position, LookAt, UpVector );
		ViewDirty = false;
	}
}

///////////////////////////////////////////////////////////////////////////////
// public projection setters

void Camera::setAspectRatio( float aspectRatio )
{
	this->aspectRatio = aspectRatio;
	ProjDirty = true;
}

void Camera::setFoVy( float FoVy )
{
	this->FoVy = FoVy;
	ProjDirty = true;
}

void Camera::setZFar( float zFar )
{
	this->zFar = zFar;
	ProjDirty = true;
}

void Camera::setZNear( float zNear )
{
	this->zNear = zNear;
	ProjDirty = true;
}

///////////////////////////////////////////////////////////////////////////////
// public view setters
void Camera::setPosition( vec3 Position )
{
	this->Position = Position;
	ViewDirty = true;
}

void Camera::setLookAt( vec3 LookAt )
{
	this->LookAt = LookAt;
	ViewDirty = true;
}

void Camera::setUpVector( vec3 UpVector )
{
	this->UpVector = UpVector;
	ViewDirty = true;
}

///////////////////////////////////////////////////////////////////////////////
// public projection getters

float Camera::getAspectRatio( void )
{
	return aspectRatio;
}

float Camera::getFoVy( void )
{
	return FoVy;
}

float Camera::getZFar( void )
{
	return zFar;
}

float Camera::getZNear( void )
{
	return zNear;
}

///////////////////////////////////////////////////////////////////////////////
// public view getters

vec3 Camera::getPosition( void )
{
	return Position;
}

vec3 Camera::getLookAt( void )
{
	return LookAt;
}

vec3 Camera::getUpVector( void )
{
	return UpVector;
}
///////////////////////////////////////////////////////////////////////////////
// public matrix getters

mat4 Camera::getProj( void )
{
	return Proj;
}

mat4 Camera::getView( void )
{
	return View;
}
