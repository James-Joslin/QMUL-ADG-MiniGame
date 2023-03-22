#include "../../include/entities/Fire.h"
#include <iostream>
#include <memory>

Fire::Fire() : Entity(EntityType::FIRE)
{
	ttlPtr = std::make_unique<TTLComponent>(startTimeToLive);
	velocityPtr = std::make_shared<VelocityComponent>();

}

Fire::~Fire()
{}

void Fire::update(Game* game, float elapsed)
{
	// XI.C First, update the position of the Fire object by calling the parent Entity::update() function.
	Entity::update(game, elapsed);

	// XI.D Time to live (Fire::ttl member variable) needs to be reduced by 1 at every frame. If this gets
	//		to 0, the entity must be deleted (here, just setting the deleted flat to ture).

	ttlPtr->update();
	velocityPtr->update(*this, elapsed);

	if (ttlPtr->getTTL() <= 0)
	{
		deleted = true;
	}

	


}
