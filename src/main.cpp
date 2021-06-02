#include "Engine.h"

int main()
{
	Engine engine = Engine();

	// object 1 creation
	engine.addObject("plane", glm::vec3(0.0f, -10.0f, 0.0f));

	// object 2 creaiton
	engine.addObject("cube", glm::vec3(0.0f, 0.0f, -5.0f));


	// portals pair creation
	//engine.addPortal(locationFirst, locationSecond);

	engine.render();

	return 0;
}