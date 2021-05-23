#pragma once

#include "EventHandler.h"
#include "Window.h"
#include "Shader.h"
#include "Level.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Engine {
public:	
	Engine() : window(),
		camera(),
		eventHandler(&camera, window.get_window(),
					window.get_width()/2, window.get_height()/2),
		level(portalShader, objectShader),
		objectShader("./data/shaders/Object_Vertex.shader", "./data/shaders/Object_Fragment.shader"),
		portalShader("./data/shaders/Portal_Vertex.shader", "./data/shaders/Portal_Fragment.shader")
	{
		setupWindow();
	}

public:

	void render()
	{
		float previousTime = glfwGetTime();
		int frameCount = 0;

		float lastFrameTime = previousTime;
		float deltaTime = 0.0f;

		while (!glfwWindowShouldClose(window.get_window()))
		{
			// Frame Counter
			float currentTime = glfwGetTime();
			if (currentTime - previousTime >= 1.0f)
			{
				// std::cout << frameCount << std::endl;
				frameCount = 0;
				previousTime = currentTime;
			}
			++frameCount;

			// Smooth Movement
			// ---------------
			deltaTime = currentTime - lastFrameTime;
			lastFrameTime = currentTime;
			// input
			// -----
			eventHandler.handleEvents(deltaTime);

			// render
			// -----
			glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			objectShader.use();

			updateShaders();
			level.Draw(camera);

			// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
			// -------------------------------------------------------------------------------
			glfwSwapBuffers(window.get_window());
			glfwPollEvents();
		}
		glfwTerminate();
	}

	void addObject(std::string objectName, glm::mat4 location) {
		location = glm::translate(location, glm::vec3(0.0f, 0.0f, 0.0f));
		level.AddObject(objectHandler.GetObject(objectName, location));
	}

	void addPortal(Portal first, Portal second) {
		level.AddPortalPair(first, second);
	}

	void addPortal(glm::mat4 locationFirst, glm::mat4 locationSecond) {
		Portal first = objectHandler.GetPortal(locationFirst);
		Portal second = objectHandler.GetPortal(locationSecond);

		first.Move(glm::vec3(-10.0f, 0.0f, 0.0f));
		second.Move(glm::vec3(10.0f, 0.0f, 0.0f));
		level.AddPortalPair(first, second);
	}


private:

	void checkSave() {
		if (glfwGetKey(window.get_window(), GLFW_KEY_P) == GLFW_PRESS)
		{
			saveWorld();
		}
	}

	void saveWorld() {
		LevelHandler::WriteLevel("./Alternative", level, camera);
	}

	void setupShaders() {
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::perspective(glm::radians(90.0f), window.get_width() / window.get_height(), 0.1f, 100.0f);

		unsigned int modelLoc = glGetUniformLocation(objectShader.ID, "model");
		unsigned int viewLoc = glGetUniformLocation(objectShader.ID, "view");
		unsigned int projectionLoc = glGetUniformLocation(objectShader.ID, "projection");

		GLuint projectionPortal = glGetUniformLocation(portalShader.ID, "projection");
		glUniformMatrix4fv(projectionPortal, 1, GL_FALSE, &projection[0][0]);
	}

	void updateShaders() 
	{
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::perspective(glm::radians(90.0f), window.get_width() / window.get_height(), 0.1f, 100.0f);

		unsigned int modelLoc = glGetUniformLocation(objectShader.ID, "model");
		unsigned int viewLoc = glGetUniformLocation(objectShader.ID, "view");
		unsigned int projectionLoc = glGetUniformLocation(objectShader.ID, "projection");

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &projection[0][0]);
	}

	glm::mat4 update_mvp()
	{
		glm::mat4 view = camera.getViewMatrix();
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), 1.0f, 0.1f, 100.0f);		//perspective view
		glm::mat4 model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
		//river.update_shaders("model", model);
		glm::mat4 mvp = projection * view * model;
		return mvp;
	}

	void setupWindow() {
		glfwMakeContextCurrent(window.get_window());
		// resizing controls
		glfwSetFramebufferSizeCallback(window.get_window(), EventHandler::framebuffer_size_callback);

		// Mouse controls
		// --------------
		glfwSetInputMode(window.get_window(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}


private:
	Window window;
	Camera camera;

	ObjectHandler objectHandler;

	Level level;

	EventHandler eventHandler;

	Shader objectShader;
	Shader portalShader;
};