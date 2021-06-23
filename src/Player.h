#pragma once

#include "Camera.h"
#include "BoundaryBox.h"
#include "Move.h"


class Player {

public:

	Player() : camera(), boundaryBox()
	{
		UpdateBoundaryBox();
	}

	Player(Camera camera_) : camera(camera_), boundaryBox()
	{
		UpdateBoundaryBox();
	}

	void Move(MoveDirection direction, float deltaTime ) 
	{
		camera.ProcessKeyboard(direction, deltaTime);
		UpdateBoundaryBox();
	}

	Player GetCopy() const 
	{
		return Player(camera);
	}

	BoundaryBox GetBoundaryBox() const
	{
		return boundaryBox;
	}

	Camera& GetCamera()
	{
		return camera;
	}

	void SetCamera(Camera cam)
	{
		camera = cam;
		UpdateBoundaryBox();
	}


	void SetHeight(float h)
	{
		height = h;
	}

	void SetRadius(float r)
	{
		radius = r;
	}

	float GetRadius() const
	{
		return radius;
	}

private:

	/**
	* Player has a height ratio of 1 to 2
	* Where the head is the 1 and the 2 is the body height
	* This function calculates the minimum point of the body  
	* and the maximum point of the head to create a boundary box
	**/
	void UpdateBoundaryBox() 
	{
		float headHeight = height / 6;
		// we were high, we are sorry
		float halfHeadHeight = headHeight / 2;
		glm::vec3 position = camera.GetPosition();
		glm::vec3 maxPoint =  position + (halfHeadHeight);
		glm::vec3 minPoint = position - (halfHeadHeight);
		minPoint.y -= height - (halfHeadHeight);

		boundaryBox.SetMinPoint(minPoint);
		boundaryBox.SetMaxPoint(maxPoint);
	}

private:
	Camera camera;
	BoundaryBox boundaryBox;
	float height = 2.5f;
	// deprecated
	float radius = 5.0f;
};
