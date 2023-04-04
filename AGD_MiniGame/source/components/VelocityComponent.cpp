#include "../../include/components/VelocityComponent.h"
#include "../../include/components/PositionComponent.h"
#include "../../include/entities/Fire.h"
#include <iostream>


void VelocityComponent::update(Entity& entity, float elapsedTime)
{
	//<FEEDBACK> Why this check? This component should only belong to the entities that have a velocity
	//<CORRECTED> If statement removed.
	entity.position->setPosition(
		entity.position->getPosition().x + (velocityDirection.x * speed * elapsedTime),
		entity.position->getPosition().y + (velocityDirection.y * speed * elapsedTime)
	);
}