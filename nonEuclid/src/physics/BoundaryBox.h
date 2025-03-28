#pragma once

#include "Move.h"

class BoundaryBox 
{

public:
	BoundaryBox() : minPoint(), maxPoint()
	{

	}

	BoundaryBox(glm::vec3 minPoint_, glm::vec3 maxPoint_) :
		minPoint(minPoint_),
		maxPoint(maxPoint_)
	{

	}

	void Move(glm::vec3 translate) 
	{
		minPoint += translate;
		maxPoint += translate;
	}

	void Move(MoveDirection direction, float speed)
	{
		switch(direction)
		{
		case FORWARD:
			Move::moveFORWARD(minPoint, speed);
			Move::moveFORWARD(maxPoint, speed);
			break;
		case BACKWARD:
			Move::moveBACKWARD(minPoint, speed);
			Move::moveBACKWARD(maxPoint, speed);
			break;
		case UPWARD:
			Move::moveUPWARD(minPoint, speed);
			Move::moveUPWARD(maxPoint, speed);
			break;
		case DOWNWARD:
			Move::moveDOWNWARD(minPoint, speed);
			Move::moveDOWNWARD(maxPoint, speed);
			break;
		case STRAFELEFT:
			Move::moveLEFT(minPoint, speed);
			Move::moveLEFT(maxPoint, speed);
			break;
		case STRAFERIGHT:
			Move::moveRIGHT(minPoint, speed);
			Move::moveRIGHT(maxPoint, speed);
			break;
		default:
			return;
		}
	}

	glm::vec3 GetMinPoint() const 
	{
		return minPoint;
	}

	glm::vec3 GetMaxPoint() const
	{
		return maxPoint;
	}

	glm::vec3 GetCenterPoint() const
	{
		return (maxPoint + minPoint) / 2.0f;
	}

	void SetMinPoint(glm::vec3 minPoint_)
	{
		minPoint = minPoint_;
	}

	void SetMaxPoint(glm::vec3 maxPoint_)
	{
		maxPoint = maxPoint_;
	}

private:
	glm::vec3 minPoint;
	glm::vec3 maxPoint;
};