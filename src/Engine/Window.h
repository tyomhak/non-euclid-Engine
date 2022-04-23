#pragma once

#include "IncludeHeaders.h"

#include <stb_image/stb_image.h>

#include <fstream>
#include <iostream>

#define WIN_WIDTH 1920
#define WIN_HEIGHT 1080

class Window
{
public:

	Window() :
		width(WIN_WIDTH),
		height(WIN_HEIGHT)
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
	GLFWwindow* GetWindow() const { return window; }

	float GetWidth() const { return width; }
	float GetHeight() const	{ return height; }
	float GetAspectRatio() const { return width / height; }

private:
	void InitializeWindow(int width, int height);


private:
	float width;
	float height;
	GLFWwindow* window;
};