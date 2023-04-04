#include "../../include/entities/Entity.h"
#include "../../include/graphics/Window.h"
#include "../../include/core/Game.h"
#include "../../include/components/PositionComponent.h"
#include "../../include/components/GraphicsComponent.h"
#include <iostream>


Entity::Entity() :
	position(std::make_unique<PositionComponent>()),
	collider(nullptr),
	id(0),
	type(EntityType::UNDEFINED),
	deleted(false)
{}

Entity::Entity(EntityType et) : 
	position( std::make_unique<PositionComponent>()),
	collider(nullptr),
	id(0),
	type (et),
	deleted(false)
{}

Entity::~Entity()
{
}

void Entity::update(Game* game, float elapsed)
{
	graphics->update(game, elapsed, getPosition());

	if (type != EntityType::FIRE)
	{
		collider->update(getPosition()); // entity getPosition calls position-> getPosition
	}
}	

void Entity::draw(Window* window)
{
	
	graphics->draw(window);

	if (type != EntityType::FIRE)
	{
		collider->draw(window);
	}
		
}

void Entity::init(const std::string& textureFile, float scale, std::shared_ptr<GraphicsComponent> _graphicsPointer)
{
	graphics = _graphicsPointer;
	graphics->init(textureFile, scale);
	Vector2f bboxSize = Vector2f(
		graphics->getTextureSize().x * graphics->getScale().x,
		graphics->getTextureSize().y * graphics->getScale().y);

	if (type != EntityType::FIRE)
	{
		collider = std::make_shared<ColliderComponent>();
		collider->setBboxSize(bboxSize);
	}
}

void Entity::initSpriteSheet(const std::string& spriteSheetFile)
{
	graphics->initSpriteSheet(spriteSheetFile);
	Vector2f bboxSize = Vector2f(
		graphics->getSpriteSize().x * graphics->getSpriteScale().x,
		graphics->getSpriteSize().y * graphics->getSpriteScale().y);

	collider = std::make_shared<ColliderComponent>();
	collider->setBboxSize(bboxSize);
}

Vector2f Entity::getPosition() // still being used by bounding box
{
	return position->getPosition();
}

void Entity::setPosition(float x, float y)
{
	position->setPosition(x, y);
	Vector2f pos = getPosition();
}	