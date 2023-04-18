#include "../../include/entities/Entity.h"
#include "../../include/graphics/Window.h"
#include "../../include/core/Game.h"
#include "../../include/components/PositionComponent.h"
#include "../../include/components/GraphicsComponent.h"
#include <iostream>


Entity::Entity() :
	position(std::make_shared<PositionComponent>()),
	collider(nullptr),
	isSpriteSheet(true),
	id(0),
	type(EntityType::UNDEFINED),
	deleted(false),
	componentSet(0)
{
	addComponent(position);
}

Entity::Entity(EntityType et) : 
	position( std::make_shared<PositionComponent>()),
	collider(nullptr),
	isSpriteSheet(true),
	id(0),
	type (et),
	componentSet(0),
	deleted(false)
{
	addComponent(position);
}

Entity::~Entity()
{
}

void Entity::init(const std::string& textureFile, float scale, std::shared_ptr<GraphicsComponent> _graphicsPointer)
{
	graphics = _graphicsPointer;
	addComponent(graphics);
	graphics->init(textureFile, scale);
	Vector2f bboxSize = Vector2f(
		graphics->getTextureSize().x * graphics->getScale().x,
		graphics->getTextureSize().y * graphics->getScale().y);

	// <FEEDBACK> Instead of doing this, put a collider (which is independent from this init() call) as a
	// component of only the classes that have collisions (i.e. static entities and players). If the development
	// of the game takes you to have many entities with no collider (quite likely), you'd end up with a long list of
	// if clauses here.
	// <CORRECTED> Implemented virtual getter in entity returns nullptr. Static Entities and Player have overrides for this
}

void Entity::initSpriteSheet(const std::string& spriteSheetFile)
{
	graphics->initSpriteSheet(spriteSheetFile);
	Vector2f bboxSize = Vector2f(
		graphics->getSpriteSize().x * graphics->getSpriteScale().x,
		graphics->getSpriteSize().y * graphics->getSpriteScale().y);

	collider = std::make_shared<ColliderComponent>();
	addComponent(collider);
	collider->setBboxSize(bboxSize);
}

Vector2f Entity::getPosition()
{
	return position->getPosition();
}

void Entity::setPosition(float x, float y)
{
	position->setPosition(x, y);
	Vector2f pos = getPosition();
	graphics->setPosition(pos); // <- this just returns a null pointer, so we're setting location via update - tabbed out update functions for objects in staticEntities.h
}	

void Entity::addComponent(std::shared_ptr<Component> c)
{
	mapComponent.insert({ c->getID(), c });
	componentSet.turnOnBit(static_cast<unsigned int>(c->getID()));
}

std::shared_ptr<ColliderComponent> Entity::getColliderComponent()
{
	return nullptr;
}

