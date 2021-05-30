#include "Engine.h"

int main()
{
	Engine engine = Engine();

	glm::mat4 location(1.0f);
<<<<<<< HEAD
	glm::mat4 cubeLocation = glm::translate(location, glm::vec3(0.0f, 0.0f, 0.0f));
	engine.addObject("backpack");
=======
	// object 1 creation
	glm::mat4 cubeLocation = glm::translate(location, glm::vec3(-5.0f, 0.0f, 0.0f));
	engine.addObject("cube", cubeLocation);
	// object 2 creaiton
>>>>>>> Collision

	cubeLocation = glm::translate(location, glm::vec3(5.0f, 0.0f, 0.0f));
	engine.addObject("cube", cubeLocation);

<<<<<<< HEAD
	location = glm::mat4(1.0f);
	glm::mat4 locationFirst = glm::translate(location, glm::vec3(0.0f, 0.0f, 10.0f));
	glm::mat4 locationSecond = glm::translate(location, glm::vec3(0.0f, 0.0f, -10.0f));

=======
	// portals location creation
	glm::mat4 locationFirst = glm::translate(location, glm::vec3(-10.0f, 0.0f, 0.0f));
	glm::mat4 locationSecond = glm::translate(location, glm::vec3(10.0f, 0.0f, 0.0f));
	// portals pair creation
>>>>>>> Collision
	engine.addPortal(locationFirst, locationSecond);

	std::cout << "temp" << std::endl;
	engine.render();

	return 0;
}