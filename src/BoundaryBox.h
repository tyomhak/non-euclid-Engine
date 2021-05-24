#pragma once

#include <glm/glm.hpp>


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
		setMinPoint(getMinPoint() + glm::vec3(translate[0], translate[1], translate[2]));
		setMaxPoint(getMaxPoint() + glm::vec3(translate[0], translate[1], translate[2]));
	}

	glm::vec3 getMinPoint() const 
	{
		return minPoint;
	}

	glm::vec3 getMaxPoint() const
	{
		return maxPoint;
	}

	void setMinPoint(glm::vec3 minPoint_)
	{
		minPoint = minPoint_;
	}

	void setMaxPoint(glm::vec3 maxPoint_)
	{
		maxPoint = maxPoint_;
	}

private:
	glm::vec3 minPoint;
	glm::vec3 maxPoint;
};