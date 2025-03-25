#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "stb_image.h"

class Window
{
public:

	Window() : Window(1920, 1080)
	{}

	Window(float width, float height) 
		: _width(width)
		, _height(height)
	{
		InitializeWindow();
	}

	~Window()
	{
		glfwDestroyWindow(_glfwWindow);
		glfwTerminate();
	}

public:
	GLFWwindow* GetWindow() const
	{
		return _glfwWindow;
	}

	int GetWidth() const
	{
		return _width;
	}

	float GetHeight() const
	{
		return _height;
	}
	float GetAspectRatio() const
	{
		return (float)_width / (float)_height;
	}


private:
	void InitializeWindow();

private:
	int _width;
	int _height;
	GLFWwindow* _glfwWindow;
};