#pragma once

#include <glm/glm.hpp>

#include "EventHandler.h"
#include "Window.h"
#include "Shader.h"
#include "Level.h"
#include "UIWindow.h"

#include "Skybox.h"

class Engine {
public:
	Engine();

public:
	void Render();

	void AddObject(std::string objectName, glm::vec3 location);
	void AddPortal(Portal first, Portal second);
	void AddPortal(glm::mat4 locationFirst, glm::mat4 locationSecond, float yawFirst = -90.0f, float yawSecond = -90.0f);

	void MoveObject(glm::vec3 direction, std::string id);
	void RotateObject(glm::vec3 direction, float angle, std::string id);

	bool CheckPlayerCollision(const std::string id);
	bool CheckCubeCollision(const std::string id1, const std::string id2);

	void TempTest();
	
	void SaveWorld();
private:

	Object* FindObjectById(std::string id);

private:
	void UpdateShaders();
	void CheckSave();
	void SetupShaders();

	void SetupWindow();

private:
	Window window;
	std::unique_ptr<ui::UIWindow> _ui_window{nullptr};
	
	Level level;
	Player player;
	Skybox skybox{};
	
	EventHandler eventHandler;

	Shader objectShader;
	Shader portalShader;
};