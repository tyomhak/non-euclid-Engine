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
		origin = camera->GetPosition();
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);

		if (height == 0)
		{
			return;
		}

		float aspectRatio = width / height;
		float x = width / 2.0f;
		float y = height / 2.0f;

		const float ndc_x = (float)((2 * ((x + 0.5) / width) - 1));
		const float ndc_y = (float)((1 - 2 * ((y + 0.5) / height)));
		const float ndc_z = (1);
		const float w = 1;

		glm::mat4 projection = glm::perspective(glm::radians(90.0f), float((float)width / (float)height), 0.1f, 100.0f);	//perspective view

		glm::vec4 ndc_vector = glm::vec4(ndc_x, ndc_y, ndc_z, w);
		direction = glm::inverse(camera->GetViewMatrix()) * glm::inverse(projection) * ndc_vector;
	}

private:
	const Camera* camera;
	GLFWwindow* window;
	glm::vec3 direction;
	glm::vec3 origin;
};