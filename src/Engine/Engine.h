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
	Engine();

public:

	void Render();

	// temporary function for testing stuff
	// made with purpose to not clutter the render loop
	// to be deleted later
	void TempTest();

	void AddObject(std::string objectName, glm::vec3 location);

	void AddPortal(Portal first, Portal second);

	void AddPortal(glm::mat4 locationFirst, glm::mat4 locationSecond, float yawFirst = -90.0f, float yawSecond = -90.0f);

	void MoveObject(glm::vec3 direction, std::string id);

	void RotateObject(glm::vec3 direction, float angle, std::string id);

	bool CheckPlayerCollision(const std::string id);
	
	bool CheckCubeCollision(const std::string id1, const std::string id2);

private:

	Object* FindObjectById(std::string id);

	void UpdateShaders();

	void CheckSave();

	void SaveWorld();

	void SetupShaders();

	void SetupWindow();

private:
	Window window;
	UI ui;

	Shader objectShader;
	Shader portalShader;

	Level level;
	Player player;

	EventHandler eventHandler;
};