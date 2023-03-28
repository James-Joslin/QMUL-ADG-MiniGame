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
	if (entity->getPlayerInputComponent())
	{
		entity->getVelocityComponent()->setVelocityDirection(0.f, 0.f);
		for (auto pointer : entity->getPlayerInputComponent()->getPlayerInputHander()->handleInput())
		{
			if (pointer)
			{
				pointer->execute(*game);
			}
		}	
	}
	else
	{

	}
}

void MovementSystem::update(Entity* entity, Game* game, float elapsedTime)
{
	if (entity->getVelocityComponent())
	{
		if (entity->getEntityType() == EntityType::PLAYER || entity->getEntityType() == EntityType::FIRE)
		{
			entity->position->setPosition(
				entity->position->getPosition().x + (entity->getVelocityComponent()->getVelocityDirection().x * entity->getVelocityComponent()->getSpeed() * elapsedTime),
				entity->position->getPosition().y + (entity->getVelocityComponent()->getVelocityDirection().y * entity->getVelocityComponent()->getSpeed() * elapsedTime)
			);
		}
	}
	else
	{

	}
}

void GameplaySystem::update(Entity* entity, Game* game, float elapsedTime)
{
	if (entity->getStateComponent())
	{
		entity->getStateComponent()->update(*entity, game, elapsedTime);
	}
}