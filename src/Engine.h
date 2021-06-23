#pragma once

#include "EventHandler.h"
#include "Window.h"
#include "Shader.h"
#include "Level.h"
#include "CollisionHandler.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "UI.h"

class Engine {
public:
	Engine() : window(),
		player(),
		level(portalShader, objectShader),
		objectShader("./data/shaders/Object_Vertex.shader", "", "./data/shaders/Object_Fragment.shader"),
		portalShader("./data/shaders/Portal_Vertex.shader", "", "./data/shaders/Portal_Fragment.shader"),
		eventHandler(&player, &level, window.GetWindow(),
			window.GetWidth() / 2, window.GetHeight() / 2, &objectShader, &portalShader),
		ui(window.GetWindow(), &eventHandler)

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


		while (!glfwWindowShouldClose(window.GetWindow()))
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

			//tempTest();

			// Smooth Movement
			// ---------------
			deltaTime = currentTime - lastFrameTime;
			lastFrameTime = currentTime;
			// input
			// -----
			eventHandler.handleEvents(deltaTime);

			// render
			// -----
			glfwPollEvents();
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			updateShaders();

			level.Draw(player.getCamera());
			ui.render();



			// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
			// -------------------------------------------------------------------------------
			glfwSwapBuffers(window.GetWindow());
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
		//objects_collision = check_cube_collision("cube1", "cube2");

		if (objects_collision == false)	// move objects only if they did not collide
		{
			//moveObject(moveRight, "cube1");
			//moveObject(moveLeft, "cube2");
			moveObject(moveLeft, "cube2");
		}

		// camera collision check
		//camera_collision = check_player_collision("cube1");

		if (camera_collision == true)
		{

		}

		//if (objects_collision == false)
		//{
		//	moveObject(moveRight, "cube1");
		//	rotateObject(glm::vec3(0.1f, 0.0f, 0.1f), 0.01f, "cube1");
		//}

		// Collision check: camera with objects
		//std::cout << "cube1 : " << check_player_collision("cube1")
		//	<< "\tcube2 : "  << check_player_collision("cube2") << std::endl;

			// Collision check: object with object
			/*std::cout << "collision : " << objects_collision << std::endl;*/

	}

	void addObject(std::string objectName, glm::vec3 location)
	{
		level.AddObject(objectName, location);
	}

	void addPortal(Portal first, Portal second)
	{
		level.AddPortalPair(first, second);
	}

	void addPortal(glm::mat4 locationFirst, glm::mat4 locationSecond, float yawFirst = -90.0f, float yawSecond = -90.0f)
	{
		Portal first = ObjectHandler::GetPortal(locationFirst);
		Portal second = ObjectHandler::GetPortal(locationSecond);

		first.yaw = yawFirst;
		second.yaw = yawSecond;

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

	void updateShaders()
	{
		glm::mat4 view = player.getCamera().getViewMatrix();
		glm::mat4 projection = glm::perspective(glm::radians(90.0f), window.GetWidth() / window.GetHeight(), 0.1f, 100.0f);	//perspective view
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
		if (glfwGetKey(window.GetWindow(), GLFW_KEY_P) == GLFW_PRESS)
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
		glm::mat4 view = player.getCamera().getViewMatrix();
		glm::mat4 projection = glm::perspective(glm::radians(90.0f), window.GetWidth() / window.GetHeight(), 0.1f, 100.0f);		//perspective view
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
		glfwMakeContextCurrent(window.GetWindow());
		// resizing controls
		glfwSetFramebufferSizeCallback(window.GetWindow(), EventHandler::framebuffer_size_callback);
		
		// Mouse controls
		// --------------
		glfwSetInputMode(window.GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}

private:
	Window window;
	Player player;

	Level level;
	
	EventHandler eventHandler;

	Shader objectShader;
	Shader portalShader;

	UI ui;
};