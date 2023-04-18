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
	// <FEEDBACK> Remove this.
	// <CORRECTED> Removed
}

void InputSystem::update(Entity* entity, Game* game, float elapsedTime)
{	
	if (entity->getComponent(ComponentID::INPUT))
	{	
		std::shared_ptr<VelocityComponent> velocity = std::dynamic_pointer_cast<VelocityComponent>(entity->getComponent(ComponentID::VELOCITY));
		std::shared_ptr<InputComponent> input = std::dynamic_pointer_cast<InputComponent>(entity->getComponent(ComponentID::INPUT));

		velocity->setVelocityDirection(0.f, 0.f);
		for (auto inputHandler : input->getPlayerInputHander()->handleInput())
		{
			// <FEEDBACK> Rename this variable.
			// <CORRECTED Pointer renamed to inputHandler
			inputHandler->execute(*game);
		}
	}
}

void MovementSystem::update(Entity* entity, Game* game, float elapsedTime)
{
	std::shared_ptr<VelocityComponent> velocity = std::dynamic_pointer_cast<VelocityComponent>(entity->getComponent(ComponentID::VELOCITY));
	std::shared_ptr<PositionComponent> position = std::dynamic_pointer_cast<PositionComponent>(entity->getComponent(ComponentID::POSITION));

	if (velocity)
	{
		// <FEEDBACK> This IF is not necessary if validate properly checks this function is called when needed.
		// <CORRECTED> If statement removed
		position->setPosition(
			position->getPosition().x + (velocity->getVelocityDirection().x * velocity->getSpeed() * elapsedTime),
			position->getPosition().y + (velocity->getVelocityDirection().y * velocity->getSpeed() * elapsedTime)
		);
	}
	// <FEEDBACK> Remove this.
	// <CORRECTED> Removed
}

void GraphicsSystem::update(Entity* entity, Game* game, float elapsedTime)
{
	std::shared_ptr<GraphicsComponent> graphics = std::dynamic_pointer_cast<GraphicsComponent>(entity->getComponent(ComponentID::GRAPHICS));
	std::shared_ptr<PositionComponent> position = std::dynamic_pointer_cast<PositionComponent>(entity->getComponent(ComponentID::POSITION));
	
	// <FEEDBACK> No need to check for the type of graphics. They all inherit from a common base class, which means that you can call the 
	// functions on the base class without worrying about the subtype.
	// <CORRECTED> Removed this type of graphics check. However, implemented methods back into GraphicsComponent (See CORRECTED_2 in GraphicsComponent). 

	if (!game->isPaused()) { graphics->update(game, elapsedTime, position->getPosition()); }
	graphics->draw(game->getWindow());
}

void ColliderSystem::update(Entity* entity, Game* game, float elapsedTime)
{
	std::shared_ptr<ColliderComponent> collider = std::dynamic_pointer_cast<ColliderComponent>(entity->getComponent(ComponentID::COLLIDER));
	// <FEEDBACK> Ok. An alternative, to alleviate logic from the component, is to make the calculations here and only set the two corners of the collider.
	// <CORRECTED> Moved logic from collider->update() to ColliderSystem::Update. Removed collider update.

	collider->getBoundingBox().setTopLeft(entity->getPosition());
	collider->getBoundingBox().setBottomRight(Vector2f((entity->getPosition().x + collider->getBboxSize().x), (entity->getPosition().y + collider->getBboxSize().y)));
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
