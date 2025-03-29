#pragma once

#include <string>

#include <glad/gl.h>
#include <GLFW/glfw3.h>


class Window
{
public:
	Window() : Window(1080, 740)
	{}

	Window(float width, float height) 
		: _width(width)
		, _height(height)
	{
		InitializeWindow();
	}

	~Window()
	{
		glfwTerminate();
	}

public:
	GLFWwindow* GetNativeWindow() { return _glfwWindow; }

	int GetWidth() const { return _width; }
	int GetHeight() const { return _height; }

	float GetAspectRatio() const
	{
		return (float)_width / (float)_height;
	}

	void SetIcon(const std::string& iconPath);

private:
	void InitializeWindow();

private:
	int _width;
	int _height;
	GLFWwindow* _glfwWindow;
};