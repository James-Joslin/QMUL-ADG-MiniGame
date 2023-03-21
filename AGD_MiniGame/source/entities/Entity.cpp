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
	// X.B (1/2) Add the initialization the deleted flag to false
	deleted(false)
{
	addComponent(position);
}

Entity::Entity(EntityType et) : 
	position( std::make_shared<PositionComponent>()),
	collider(nullptr),
	isSpriteSheet(true),
	id(0),
	type (et),
	// X.B (2/2) Add the initialization the deleted flag to false
	deleted(false)

{
	addComponent(position);
}

Entity::~Entity()
{
}

void Entity::update(Game* game, float elapsed)
{

	// VI.D: Update the position of X and Y by adding the corresponding velocity coordinate.
	//       This movement needs to be per second, so you need to factor in the speed of the entity 
	//       (which is a member variable of this class) and the elapsed time since the last frame 
	//       (a parameter in this function).
	
	
	// IV.D (2/2) If this entity has a spritesheet (variable "isSpriteSheet" is true), do two operations:
	//              i)  Set the sprite position of the spritesheet to the position of this entity.
	//              ii) Call update on the spriteSheet, passing the delta time of this update call.
	//				If the entity does NOT have a spritesheet ("isSpriteSheet" is false, {else} clause), simply:
	//			    iii) set the position of the "sprite" variable to the position vector (using sprite.setPosition(...)).
	

	//Need to implement an update in graphics component
	graphics->update(game, elapsed, getPosition()); // hasn't been implemented yet

	//if (isSpriteSheet) // <- Needs to go into graphicsPointer->Update()
	//{
	//	const Vector2f position = getPosition();
	//	spriteSheet.setSpritePosition(sf::Vector2f(position.x, position.y));
	//	spriteSheet.update(elapsed);
	//}
	//else // <- Needs to go into graphicsPointer->Update()
	//{
	//	sprite.setPosition(sf::Vector2f(position->getPosition().x, position->getPosition().y));
	//}

	// VIII.A  The bounding box of an entity has the same dimensions as the texture of the sprite
	//		   or spritesheet. This is calculated in the init() functions (see below in this file)
	//		   and the size is stored in the variable "bboxSize". 
	//		   The member variable boundingBox is a Rectangle where we'll hold this boundary box. 
	//		   Set the top left corner of this rectangle to the position of this entity.
	//		   Set the bottom right corner of this rectangle to the position+bboxSize coordinates.
	
	
	//Rectangle& bbox = getBoundingBox();
	if (type != EntityType::FIRE)
	{
		collider->update(getPosition()); // entitiy getPosition calls position-> getPosition
	}
}	

void Entity::draw(Window* window)
{
	
	graphics->draw(window); // or should the draw still be in the entity class?
	//if (isSpriteSheet)
	//{
	//	sf::Sprite* sp = &spriteSheet.getSprite();
	//	const sf::Vector2f pos = sp->getPosition();
	//	window->draw(spriteSheet.getSprite());
	//}
	//else
	//	window->draw(sprite); 

	// VIII.B Draw the bounding box by retrieving a drawable rect from the bounding box Rectangle.
	if (type != EntityType::FIRE)
	{
		collider->draw(window);
	}
		
}

void Entity::init(const std::string& textureFile, float scale, std::shared_ptr<GraphicsComponent> _graphicsPointer)
{
	graphics = _graphicsPointer;
	graphics->init(textureFile, scale);
	//texture.loadFromFile(textureFile);
	//sprite.setTexture(texture);
	//sprite.setScale(scale, scale);
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
	/*spriteSheet.loadSheet(spriteSheetFile);
	isSpriteSheet = true;
	spriteSheet.setAnimation("Idle", true, true);*/
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
	std::cout << pos.x << pos.y << std::endl;
	// graphicsPointer->setPosition(pos);  <- this just returns a null pointer, so we're setting location via update - tabbed out update functions for objects in staticEntities.h

	//if (graphicsPointer)
	//{
	//}
	/*if( graphicsPointer )
		graphicsPointer->getSpriteSheet()->getSprite().setPosition(
			position->getPosition().x,
			position->getPosition().y);*/
	//else
	//	graphicsPointer->getSprite().setPosition(
	//		position->getPosition().x,
	//		position->getPosition().y);
}	

void Entity::addComponent(std::shared_ptr<Component> something)
{
	componentSet.turnOnBit(static_cast<unsigned int>(something->getID()));
}

std::shared_ptr<TTLComponent> Entity::getTTLComponent()
{
	return nullptr;
}
