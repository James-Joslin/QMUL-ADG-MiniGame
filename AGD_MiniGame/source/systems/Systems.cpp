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
	if (entity->getComponent(ComponentID::TTL))
	{
		std::shared_ptr<TTLComponent> ttl = std::dynamic_pointer_cast<TTLComponent>(entity->getComponent(ComponentID::TTL));

		ttl->decrementTTL();
		if (ttl->getTTL() <= 0)
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
	if (entity->getComponent(ComponentID::INPUT))
	{	
		std::shared_ptr<VelocityComponent> velocity = std::dynamic_pointer_cast<VelocityComponent>(entity->getComponent(ComponentID::VELOCITY));
		std::shared_ptr<InputComponent> input = std::dynamic_pointer_cast<InputComponent>(entity->getComponent(ComponentID::INPUT));

		velocity->setVelocityDirection(0.f, 0.f);
		for (auto pointer : input->getPlayerInputHander()->handleInput())
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
	std::shared_ptr<VelocityComponent> velocity = std::dynamic_pointer_cast<VelocityComponent>(entity->getComponent(ComponentID::VELOCITY));
	std::shared_ptr<PositionComponent> position = std::dynamic_pointer_cast<PositionComponent>(entity->getComponent(ComponentID::POSITION));

	if (velocity)
	{
		if (entity->getEntityType() == EntityType::PLAYER || entity->getEntityType() == EntityType::FIRE)
		{
			position->setPosition(
				position->getPosition().x + (velocity->getVelocityDirection().x * velocity->getSpeed() * elapsedTime),
				position->getPosition().y + (velocity->getVelocityDirection().y * velocity->getSpeed() * elapsedTime)
			);



		}
		//if (entity->getEntityType() == EntityType::FIRE)
		//{
		//	std::cout << position->getPosition().x << " hello" << std::endl;
		//	//std::cout << velocity->getPosition().x << " hello" << std::endl;
		//}
	}
	else
	{

	}
}

void GraphicsSystem::update(Entity* entity, Game* game, float elapsedTime)
{
	std::shared_ptr<GraphicsComponent> graphics = std::dynamic_pointer_cast<GraphicsComponent>(entity->getComponent(ComponentID::GRAPHICS));
	graphics->draw(game->getWindow());
}

void ColliderSystem::update(Entity* entity, Game* game, float elapsedTime)
{
	std::shared_ptr<ColliderComponent> collider = std::dynamic_pointer_cast<ColliderComponent>(entity->getComponent(ComponentID::COLLIDER));

	collider->update(entity->getPosition());
	//entity->getColliderComponent()->draw(game->getWindow()); // <- broken like graphics draw method

}

void GameplaySystem::update(Entity* entity, Game* game, float elapsedTime)
{
	std::shared_ptr<PlayerStateComponent> state = std::dynamic_pointer_cast<PlayerStateComponent>(entity->getComponent(ComponentID::STATE));

	state->update(*entity, game, elapsedTime);
}
