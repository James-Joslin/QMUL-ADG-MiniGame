#pragma once
#include "../utils/Vector2.h"
#include "../entities/Entity.h"

class VelocityComponent
{

public:
	VelocityComponent() : speed{ 1.f } {}
	VelocityComponent(float _speed) : speed{ _speed } {}
	
	void setVelocityDirection(float x, float y) 
	{
		velocityDirection.x = x; 
		velocityDirection.y = y;
	}
	const Vector2f getVelocityDirection() { return velocityDirection; }

	void update(Entity&, float);

private:
	Vector2f velocityDirection;
	float speed;

	

};