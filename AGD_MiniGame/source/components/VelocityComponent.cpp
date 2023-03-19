#include "../../include/components/VelocityComponent.h"
#include "../../include/components/PositionComponent.h"
#include "../../include/entities/Fire.h"
#include <iostream>


void VelocityComponent::update(Entity& entity, float elapsedTime)
{
	if (entity.getEntityType() == EntityType::PLAYER || entity.getEntityType() == EntityType::FIRE)
	{
		entity.position->setPosition(
			entity.position->getPosition().x + (velocityDirection.x * speed * elapsedTime),
			entity.position->getPosition().y + (velocityDirection.y * speed * elapsedTime)
		);
	}
}