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
		// <FEEDBACK> Remove this.
	}
}

void InputSystem::update(Entity* entity, Game* game, float elapsedTime)
{	
	if (entity->getComponent(ComponentID::INPUT))
	{	
		// code that was in the input component update -> should update code be put back and all we do in the system is call the update
		// code of the component via a pointer?
		std::shared_ptr<VelocityComponent> velocity = std::dynamic_pointer_cast<VelocityComponent>(entity->getComponent(ComponentID::VELOCITY));
		std::shared_ptr<InputComponent> input = std::dynamic_pointer_cast<InputComponent>(entity->getComponent(ComponentID::INPUT));

		// Code that was in velocity update function
		velocity->setVelocityDirection(0.f, 0.f);
		for (auto pointer : input->getPlayerInputHander()->handleInput())
		{
			if (pointer) // <FEEDBACK> Rename this variable.
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

	// Code that was in the movement system update
	if (velocity)
	{
		// <FEEDBACK> This IF is not necessary if validate properly checks this function is called when needed.
		if (entity->getEntityType() == EntityType::PLAYER || entity->getEntityType() == EntityType::FIRE)
		{
			position->setPosition(
				position->getPosition().x + (velocity->getVelocityDirection().x * velocity->getSpeed() * elapsedTime),
				position->getPosition().y + (velocity->getVelocityDirection().y * velocity->getSpeed() * elapsedTime)
			);
		}
	}
	else
	{
		// <FEEDBACK> Remove this.
	}
}

void GraphicsSystem::update(Entity* entity, Game* game, float elapsedTime)
{
	std::shared_ptr<GraphicsComponent> graphics = std::dynamic_pointer_cast<GraphicsComponent>(entity->getComponent(ComponentID::GRAPHICS));
	std::shared_ptr<PositionComponent> position = std::dynamic_pointer_cast<PositionComponent>(entity->getComponent(ComponentID::POSITION));
	
	// <FEEDBACK> No need to check for the type of graphics. They all inherit from a common base class, which means that you can call the 
	// functions on the base class without worrying about the subtype.


	// code that was in graphics pointer update
	if (graphics->isSpriteSheetEntity())
	{
		// updating graphic positioning
		graphics->getSpriteSheet()->setSpritePosition(sf::Vector2f(position->getPosition().x, position->getPosition().y));
		graphics->getSpriteSheet()->update(elapsedTime);

		// draw - being called in game::render()
		// just calling draw in graphics component via pointer
		game->getWindow()->draw(graphics->getSpriteSheet()->getSprite());
	}
	else
	{
		sf::Sprite* sprite = graphics->getSprite();
		sprite->setPosition(sf::Vector2f(position->getPosition().x, position->getPosition().y));

		// draw being handled in game::render()
		game->getWindow()->draw(*sprite);
	}	
}

void ColliderSystem::update(Entity* entity, Game* game, float elapsedTime)
{
	std::shared_ptr<ColliderComponent> collider = std::dynamic_pointer_cast<ColliderComponent>(entity->getComponent(ComponentID::COLLIDER));
	// <FEEDBACK> Ok. An alternative, to alleviate logic from the component, is to make the calculations here and only set the two corners of the collider.
	collider->update(entity->getPosition());

}

void PrintDebugSystem::update(Entity* entity, Game* game, float elapsedTime)
{
	std::shared_ptr<ColliderComponent> collider = std::dynamic_pointer_cast<ColliderComponent>(entity->getComponent(ComponentID::COLLIDER));
	collider->draw(game->getWindow());
}

void GameplaySystem::update(Entity* entity, Game* game, float elapsedTime)
{
	std::shared_ptr<PlayerStateComponent> state = std::dynamic_pointer_cast<PlayerStateComponent>(entity->getComponent(ComponentID::STATE));

	state->update(*entity, game, elapsedTime);
}
