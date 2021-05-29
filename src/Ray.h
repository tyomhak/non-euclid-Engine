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
		createRay();
	}


public:

	glm::vec3 getOrigin() const
	{
		return origin;
	}

	glm::vec3 getDirection() const
	{
		return direction;
	}

private:
	void createRay()
	{
		origin = camera->getPosition();
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);

		float aspectRatio = width / height;
		float x = width / 2.0f;
		float y = height / 2.0f;

		const float camera_x = (float)((2 * ((x + 0.5) / width) - 1) * tanf((camera->get_FOV()) / 2 * PI / 180) * aspectRatio);
		const float camera_y = (float)((1 - 2 * ((y + 0.5) / height)) * tanf((camera->get_FOV()) / 2 * PI / 180));
		//const float length = (float)(sqrt((camera_x * camera_x) + (camera_y * camera_y) + 1));
		//direction = glm::vec3(camera_x / length, camera_y / length, (-1) / length);
		direction = glm::vec3(camera_x, camera_y, (-1.0f));
	}

private:
	const Camera* camera;
	GLFWwindow* window;
	glm::vec3 direction;
	glm::vec3 origin;
};