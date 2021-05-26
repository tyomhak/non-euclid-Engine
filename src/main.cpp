#include "Engine.h"

int main()
{
	Engine engine = Engine();

	glm::mat4 location(1.0f);
	// object 1 creation
	glm::mat4 cubeLocation = glm::translate(location, glm::vec3(-5.0f, 0.0f, 0.0f));
	engine.addObject("cube", cubeLocation);
	// object 2 creaiton

	cubeLocation = glm::translate(location, glm::vec3(5.0f, 0.0f, 0.0f));
	engine.addObject("cube", cubeLocation);

	// portals location creation
	glm::mat4 locationFirst = glm::translate(location, glm::vec3(-10.0f, 0.0f, 0.0f));
	glm::mat4 locationSecond = glm::translate(location, glm::vec3(10.0f, 0.0f, 0.0f));
	// portals pair creation
	engine.addPortal(locationFirst, locationSecond);

	engine.render();

	return 0;
}