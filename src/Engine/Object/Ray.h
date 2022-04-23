#pragma once

#include "Camera.h"
#include "Window.h"

#define PI 3.14159265

class Ray
{
public:
	Ray(Camera* _camera, GLFWwindow* _window) :
		camera(_camera),
		window(_window)
	{
		CreateRay();
	}


public:

	glm::vec3 GetOrigin() const { return origin; }

	glm::vec3 GetDirection() const { return direction; }

private:
	void CreateRay();

private:
	const Camera* camera;
	GLFWwindow* window;
	glm::vec3 direction;
	glm::vec3 origin;
};