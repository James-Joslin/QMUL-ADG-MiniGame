#include "../../include/systems/Systems.h"
#include "../../include/core/Game.h"
#include "../../include/entities/Player.h"
#include "../../include/components/InputComponent.h"
#include "../../include/core/InputHandler.h"
#include "../../include/core/Command.h"
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

void InputSystem::update(Entity* entity, Game* game, float elapsedTime)
{
	auto v = game->getPlayer()->getVelocityComp();
	v->setVelocityDirection(0.f, 0.f);

	
	
	if (entity->getPlayerInputComponent())
	{
		//std::cout << entity->getPlayerInputComponent() << std::endl;
		for (auto pointer : entity->getPlayerInputComponent()->getPlayerInputHander()->handleInput())
		{
			if (pointer)
			{
				//std::cout << pointer << std::endl;
				// handle non-null pointer case
				pointer->execute(*game);
			}
		}	
	}
	else
	{
		//std::cout << entity->getPlayerInputComponent() << std::endl;
	}
}