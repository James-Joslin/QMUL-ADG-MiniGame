#include "../../include/entities/Fire.h"
#include <iostream>
#include <memory>

Fire::Fire() : Entity(EntityType::FIRE)
{
	ttlPtr = std::make_shared<TTLComponent>(startTimeToLive);
	addComponent(ttlPtr);

	velocityPtr = std::make_shared<VelocityComponent>();
	addComponent(velocityPtr);
}

Fire::~Fire()
{}
