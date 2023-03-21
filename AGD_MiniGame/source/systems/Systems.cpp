#include "../../include/systems/Systems.h"
#include "../../include/core/Game.h"
#include <stdexcept>
#include <iostream>

void TTLSystem::update(Entity* entity, Game* game, float elapsedTime)
{
	if (entity->getTTLComponent())
	{
		entity->getTTLComponent()->decrementTTL();
		if (entity->getTTLComponent()->getTTL() <= 0)
		{
			entity->markDeleted();
		}
	}
	else
	{
		
	}
}