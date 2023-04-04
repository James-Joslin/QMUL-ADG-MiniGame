#pragma once
#include "../../include/utils/Vector2.h"


class PositionComponent
{
public:
	//PositionComponent();
	const Vector2f& getPosition() const { return position; }
	void setPosition(float x, float y)
	{
		position.x = x; position.y = y;
	}

private:
	Vector2f position;

};