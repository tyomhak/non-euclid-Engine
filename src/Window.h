#pragma once

#include "IncludeHeaders.h"

#include <stb_image/stb_image.h>

#include <fstream>
#include <iostream>

class Window
{
public:

	Window() :
		width(1024),
		height(768)
	{
		initialize_window(width, height);
	}

	Window(int wid, int hei) :
		width(wid),
		height(hei)
	{
		initialize_window(wid, hei);
	}

public:
	GLFWwindow* get_window() const
	{
		return window;
	}

	float get_width() const
	{
		return width;
	}

	float get_height() const
	{
		return height;
	}


private:
	void initialize_window(int width, int height)
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
		//window = glfwCreateWindow(width, height, "River", glfwGetPrimaryMonitor(), NULL);
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