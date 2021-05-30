#pragma once

#include "EventHandler.h"
#include "Window.h"
#include "Shader.h"
#include "Level.h"

#include "CollisionHandler.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Engine {
public:
	Engine() : window(),
		player(),
		eventHandler(&player, &level, window.get_window(),
			window.get_width() / 2, window.get_height() / 2),
		level(portalShader, objectShader),
		objectShader("./data/shaders/Object_Vertex.shader", "./data/shaders/Object_Fragment.shader"),
		portalShader("./data/shaders/Portal_Vertex.shader", "./data/shaders/Portal_Fragment.shader")
	{
		setupWindow();

	}

public:

	void render()
	{
		float previousTime = (float)glfwGetTime();
		int frameCount = 0;

		float lastFrameTime = previousTime;
		float deltaTime = 0.0f;


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

			tempTest();

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

			portalShader.use();
			updateShaders();
			objectShader.use();
			updateShaders();
			
			level.Draw(player.getCamera());


			// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
			// -------------------------------------------------------------------------------
			glfwSwapBuffers(window.get_window());
			glfwPollEvents();
		}
		glfwTerminate();
	}

	// temporary function for testing stuff
	// made with purpose to not clutter the render loop
	// to be deleted later
	void tempTest() 
	{
		bool objects_collision = false;
		bool camera_collision = false;

		static glm::vec3 moveRight = glm::vec3(0.01f, 0.0f, 0.0f);
		static glm::vec3 moveLeft = glm::vec3(-0.01f, 0.0f, 0.0f);
		static glm::vec3 moveUp = glm::vec3(0.0f, 0.0075f, 0.0f);

		// objects collision check
		objects_collision = check_cube_collision("cube1", "cube2");

		if (objects_collision == false)	// move objects only if they did not collide
		{
			//moveObject(moveRight, "cube1");
			//moveObject(moveLeft, "cube2");
			moveObject(moveLeft, "cube2");
		}

		// camera collision check
		camera_collision = check_player_collision("cube1");

		if (camera_collision == true)
		{

		}

		//if (objects_collision == false)
		//{
		//	moveObject(moveRight, "cube1");
		//	rotateObject(glm::vec3(0.1f, 0.0f, 0.1f), 0.01f, "cube1");
		//}

		// Collision check: camera with objects
		std::cout << "cube1 : " << check_player_collision("cube1")
			<< "\tcube2 : "  << check_player_collision("cube2") << std::endl;

			// Collision check: object with object
			/*std::cout << "collision : " << objects_collision << std::endl;*/

	}

	void addObject(std::string objectName, glm::mat4 location)
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

	void rotateObject(glm::vec3 direction, float angle, std::string id)
	{
		Object* objectToMove = findObjectById(id);
		objectToMove->rotate(angle, direction);
	}

	bool check_player_collision(const std::string id)
	{
		return CollisionHandler::check_collision(player, level.GetObjects().at(id));
	}
	bool check_cube_collision(const std::string id1, const std::string id2)
	{
		// TODO: handle case when element was not found in the map by ID
		return CollisionHandler::check_collision(level.GetObjects().at(id1), level.GetObjects().at(id2));
	}

private:

	Object* findObjectById(std::string id)
	{
		return &level.GetObjects().at(id);
	}

private:

	void checkSave()
	{
		if (glfwGetKey(window.get_window(), GLFW_KEY_P) == GLFW_PRESS)
		{
			saveWorld();
		}
	}

	void saveWorld()
	{
		LevelHandler::WriteLevel("./Alternative", level, player.getCamera());
	}

	void setupShaders()
	{
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
		glm::mat4 view = player.getCamera().getViewMatrix();
		glm::mat4 projection = glm::perspective(glm::radians(player.getCamera().Zoom), 1.0f, 0.1f, 100.0f);		//perspective view
		glm::mat4 model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
		//river.update_shaders("model", model);
		glm::mat4 mvp = projection * view * model;
		return mvp;
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
	Player player;

	Level level;
	
	ObjectHandler objectHandler;
	EventHandler eventHandler;

	Shader objectShader;
	Shader portalShader;
};