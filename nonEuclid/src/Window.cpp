#include "Window.h"

#include <iostream>

void Window::InitializeWindow()
{
	if (glfwInit() != GLFW_TRUE) { return; }

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	/* Create a windowed mode window and its OpenGL context */
	//window = glfwCreateWindow(width, height, "LearnOpenGL", glfwGetPrimaryMonitor(), NULL);
	_glfwWindow = glfwCreateWindow(_width, _height, "LearnOpenGL", NULL, NULL);

	if (!_glfwWindow)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}

	glfwSwapInterval(1);
	/* Make the window's context current */
	glfwMakeContextCurrent(_glfwWindow);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	// if (!gladLoadGLLoader((GLADloadfunc)glfwGetProcAddress))
	if (!gladLoaderLoadGL())
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
