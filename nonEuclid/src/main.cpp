#include "Engine.h"

int main()
{
	Engine engine = Engine();

	// object 1 creation
	engine.AddObject("plane", glm::vec3(0.0f, -10.0f, 0.0f));

	// object 2 creaiton
	engine.AddObject("cube", glm::vec3(0.0f, 0.0f, -5.0f));
	engine.AddObject("cube", glm::vec3(5.0f, 0.0f, -5.0f));
	engine.AddObject("cube", glm::vec3(10.0f, 0.0f, -5.0f));

	glm::mat4 location = glm::mat4(1.0f);
	glm::mat4 locationFirst = glm::translate(location, glm::vec3(10.0f, 0.0f, 10.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(3.0f, 3.0f, 3.0f));
	glm::mat4 locationSecond = glm::translate(location, glm::vec3(-10.0f, 0.0f, -10.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(3.0f, 3.0f, 3.0f));
	// portals pair creation
	engine.AddPortal(locationFirst, locationSecond);

	// portals pair creation
	//engine.AddPortal(locationFirst, locationSecond);

	engine.Render();

	return 0;
}