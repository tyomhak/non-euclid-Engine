#include "Engine.h"

int main()
{
	Engine engine = Engine();

	glm::vec3 location = glm::vec3(-10.0f, -5.0f, -5.0f);
	engine.addObject("backpack", location);

	engine.render();
	return 0;
}