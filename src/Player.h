#pragma once

#include "Camera.h"
#include "BoundaryBox.h"
#include "Move.h"


class Player {

public:

	Player() : camera(), boundaryBox()
	{
	}

	Player(Camera camera_) : camera(camera_), boundaryBox()
	{
		updateBoundaryBox();
	}

	// Player(Player& const) {

	// }

	void move(MoveDirection direction, float deltaTime ) 
	{
		camera.ProcessKeyboard(direction, deltaTime);
		updateBoundaryBox();
	}

	BoundaryBox getBoundaryBox() const
	{
		return boundaryBox;
	}

	Camera& getCamera()
	{
		return camera;
	}


	void setHeight(float h)
	{
		height = h;
	}

private:

	/**
	* Player has a height ratio of 1 to 2
	* Where the head is the 1 and the 2 is the body height
	* This function calculates the minimum point of the body  
	* and the maximum point of the head to create a boundary box
	**/
	void updateBoundaryBox() 
	{
		float headHeight = height / 3;
		// we were high, we are sorry
		float halfHeadHeight = headHeight / 2;
		glm::vec3 position = camera.getPosition();
		glm::vec3 maxPoint =  position + (halfHeadHeight);
		glm::vec3 minPoint = position - (halfHeadHeight);
		minPoint.y -= height - (halfHeadHeight);

		boundaryBox.setMinPoint(minPoint);
		boundaryBox.setMaxPoint(maxPoint);
	}

private:
	Camera camera;
	BoundaryBox boundaryBox;
	float width = 0.5f;
	float height = 1.5f;

};
