#pragma once

#include "IncludeHeaders.h"

#include <stb_image/stb_image.h>

#include <fstream>
#include <iostream>

class Window
{
public:

	Window() :
		width(1920),
		height(1080)
	{
		InitializeWindow((int)width, (int)height);
	}

	Window(int wid, int hei) :
		width((float)wid),
		height((float)hei)
	{
		InitializeWindow(wid, hei);
	}

public:
	GLFWwindow* GetWindow() const
	{
		return window;
	}

	float GetWidth() const
	{
		return width;
	}

	float GetHeight() const
	{
		return height;
	}
	float GetAspectRatio() const
	{
		return width / height;
	}


private:
	void InitializeWindow(int width, int height)
	{
		/* Initialize the library */
		if (!glfwInit()) { return; }

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		#ifdef __APPLE__
				glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		#endif

		/* Create a windowed mode window and its OpenGL context */
		//window = glfwCreateWindow(width, height, "LearnOpenGL", glfwGetPrimaryMonitor(), NULL);
		window = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);

		if (!window)
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			return;
		}

		glfwSwapInterval(1);
		/* Make the window's context current */
		glfwMakeContextCurrent(window);

		// glad: load all OpenGL function pointers
		// ---------------------------------------
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			return;
		}

		// flip textures on y-axis
		stbi_set_flip_vertically_on_load(true);


		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		// glCullFace(GL_BACK);
		// glFrontFace(GL_CW); 
	}

private:
	float width;
	float height;
	GLFWwindow* window;
};