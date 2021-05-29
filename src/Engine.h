#pragma once

#include "EventHandler.h"
#include "Window.h"
#include "Shader.h"
#include "Level.h"

#include "AABB.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Engine {
public:
	Engine() : window(),
		camera(),
		eventHandler(&camera, window.get_window(),
		window.get_width() / 2, window.get_height() / 2),
		level(portalShader, objectShader),
		objectShader("./data/shaders/Object_Vertex.shader", "", "./data/shaders/Object_Fragment.shader"),
		portalShader("./data/shaders/Portal_Vertex.shader", "", "./data/shaders/Portal_Fragment.shader")
	{
		setupWindow();
		setupShaders();
	}

public:

	void render()
	{
		float previousTime = (float)glfwGetTime();
		int frameCount = 0;

		float lastFrameTime = previousTime;
		float deltaTime = 0.0f;

		glm::vec3 moveRight = glm::vec3(0.01f, 0.0f, 0.0f);
		glm::vec3 moveLeft = glm::vec3(-0.01f, 0.0f, 0.0f);

		while (!glfwWindowShouldClose(window.get_window()))
		{
			// Frame Counter
			float currentTime = (float)glfwGetTime();
			if (currentTime - previousTime >= 1.0f)
			{
				 std::cout << frameCount << std::endl;
				frameCount = 0;
				previousTime = currentTime;
			}
			++frameCount;

			//moveObject(moveRight, "cube1");
			//moveObject(moveLeft, "cube2");

			
			// Collision check: camera with objects
			// ----------------------
			//std::cout << "cube1 : " << check_collision("cube1")
			//	<< "\tcube2 : " << check_collision("cube2") << std::endl;
			//
			
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

			updateShaders();

			level.Draw(camera);



			// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
			// -------------------------------------------------------------------------------
			glfwSwapBuffers(window.get_window());
			glfwPollEvents();
		}
		glfwTerminate();
	}


	void addObject(std::string objectName, glm::mat4 location = glm::mat4(1.0f))
	{
		level.AddObject(objectHandler.GetObject(objectName, location));
	}

	void addPortal(Portal first, Portal second)
	{
		level.AddPortalPair(first, second);
	}

	void addPortal(glm::mat4 locationFirst, glm::mat4 locationSecond)
	{
		Portal first = objectHandler.GetPortal(locationFirst);
		Portal second = objectHandler.GetPortal(locationSecond);

		level.AddPortalPair(first, second);
	}

	void moveObject(glm::vec3 direction, std::string id)
	{
		Object* objectToMove = findObjectById(id);
		objectToMove->Move(direction);
	}

	bool check_collision(const std::string id)
	{
		return AABB::intersect(camera, level.GetObjects().at(id));
	}

private:

	Object* findObjectById(std::string id)
	{
		return &level.GetObjects().at(id);
	}

private:

	void updateShaders()
	{
		glm::mat4 view = camera.getViewMatrix();
		glm::mat4 projection = glm::perspective(glm::radians(90.0f), window.get_width() / window.get_height(), 0.1f, 100.0f);	//perspective view
		glm::mat4 model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
		glm::mat4 mvp = projection* view* model;
		objectShader.bind();
		objectShader.SetMat4("mvp", mvp);

		//objectShader.update();

		portalShader.bind();
		portalShader.SetMat4("mvp", mvp);
		//portalShader.unbind();
	}

	void checkSave()
	{
		if (glfwGetKey(window.get_window(), GLFW_KEY_P) == GLFW_PRESS)
		{
			saveWorld();
		}
	}

	void saveWorld()
	{
		LevelHandler::WriteLevel("./Alternative", level, camera);
	}

	void setupShaders()
	{
		glm::mat4 view = camera.getViewMatrix();
		glm::mat4 projection = glm::perspective(glm::radians(90.0f), window.get_width() / window.get_height(), 0.1f, 100.0f);		//perspective view
		glm::mat4 model = glm::mat4(1.0f);

		objectShader.setView(view);
		objectShader.setModel(model);
		objectShader.setProjection(projection);

		portalShader.setView(view);
		portalShader.setModel(model);
		portalShader.setProjection(projection);

	}

	void setupWindow()
	{
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

	Level level;
	
	ObjectHandler objectHandler;
	EventHandler eventHandler;

	Shader objectShader;
	Shader portalShader;
};