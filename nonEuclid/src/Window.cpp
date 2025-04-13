#include "Window.h"

#include <iostream>

#include "utils/stb_image.h"

void Window::InitializeWindow()
{
	if (glfwInit() != GLFW_TRUE) { return; }

	glfwWindowHint(GLFW_SAMPLES, 8); // antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	/* Create a windowed mode window and its OpenGL context */
	const bool fullscreen = false;
	GLFWmonitor* monitor = fullscreen ? glfwGetPrimaryMonitor() : nullptr;
	_glfwWindow = glfwCreateWindow(_width, _height, "Non Euclid Engine", monitor, NULL);
	if (!_glfwWindow)
	{
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}

	GLFWimage images[1]; 
	images[0].pixels = stbi_load("./data/icons/Euclid.jpg", &images[0].width, &images[0].height, 0, 4); //rgba channels 
	glfwSetWindowIcon(_glfwWindow, 1, images); 
	stbi_image_free(images[0].pixels);

	glfwSwapInterval(0);
	/* Make the window's context current */
	glfwMakeContextCurrent(_glfwWindow);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	// if (!gladLoadGLLoader((GLADloadfunc)glfwGetProcAddress))
	if (!gladLoaderLoadGL())
	{
		std::cerr << "Failed to initialize GLAD" << std::endl;
		return;
	}

	// flip textures on y-axis
	stbi_set_flip_vertically_on_load(true);


	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	// glCullFace(GL_BACK);
	// glFrontFace(GL_CW); 
}



void Window::SetIcon(const std::string& iconPath)
{
	stbi_set_flip_vertically_on_load(false);
	GLFWimage images[1];
	images[0].pixels = stbi_load(iconPath.c_str(), &images[0].width, &images[0].height, 0, 4); //rgba channels 
	glfwSetWindowIcon(_glfwWindow, 1, images); 
	stbi_image_free(images[0].pixels);
	stbi_set_flip_vertically_on_load(true);
}
