#pragma once
#include "../graphics/Window.h"
#include "../utils/Rectangle.h"
#include "../../include/components/GraphicsComponent.h"
#include <memory>

class PositionComponent;

using EntityID = unsigned int;
enum class EntityType
{
	UNDEFINED = -1,
	PLAYER = 0,
	POTION = 1,
	LOG = 2,
	FIRE = 3
};

class Game; //forward declaration

class Entity
{
public:

	//Constructors and Desctrutors
	Entity();
	Entity(EntityType et);
	~Entity();

	//Init and update functions
	virtual void init(const std::string& textureFile, float scale, std::shared_ptr<GraphicsComponent> _graphicsPointer);
	void initSpriteSheet(const std::string& spriteSheetFile);
	virtual void update(Game* game, float elapsed = 1.0f);
	void draw(Window* window);

	//Getters and Setters
	void setID(EntityID entId) { id = entId; }
	EntityID getID() const { return id; }
	void setPosition(float x, float y);
	Vector2f getPosition();
	Rectangle& getBoundingBox() { return boundingBox; };
	//const sf::Vector2f& getSpriteScale() const;
//	sf::Vector2i getTextureSize() const;
	EntityType getEntityType() const { return type; }
	SpriteSheet* getSpriteSheet() { return graphicsPointer->getSpriteSheet(); }
	bool isSpriteSheetEntity() const { return isSpriteSheet; }
	
	// X.C  Add two helper functions. One that returns the value of the deleted flag, another one that 
	//      "deletes" the entity by setting this flag to true. (Q: one of this functions should be "const", which one?).
	bool isDeleted() const { return deleted; }
	void markDeleted() { deleted = true; }

protected:

	EntityType type;
	EntityID id;


	//Collision
	Rectangle boundingBox;
	Vector2f bboxSize;

	//Graphics-related variables.
	bool isSpriteSheet;
	//SpriteSheet spriteSheet;
	//sf::Texture texture;
	//sf::Sprite sprite;

	// X.A Add a bool member variable "deleted" to this class.
	bool deleted;

	//Position and velocity
	std::unique_ptr<PositionComponent> position;
	std::shared_ptr<GraphicsComponent> graphicsPointer;
};