#pragma once
#include "../graphics/Window.h"
#include "../utils/Rectangle.h"
#include "../../include/components/GraphicsComponent.h"
#include "../components/ColliderComponent.h"
#include "../utils/Bitmask.h"
#include "../components/TTLComponent.h"
#include <memory>

class PositionComponent;
class InputComponent;
class VelocityComponent;
class PlayerStateComponent;

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
	virtual void init(const std::string& textureFile, float scale, std::shared_ptr<GraphicsComponent> _graphics);
	void initSpriteSheet(const std::string& spriteSheetFile);
	virtual void update(Game* game, float elapsed = 1.0f);
	void draw(Window* window);

	
	void addComponent(std::shared_ptr<Component> c);
	std::shared_ptr<Component> getComponent(ComponentID id)
	{
		return mapComponent[id];
	}
	

	//virtual std::shared_ptr<TTLComponent> getTTLComponent();
	//virtual std::shared_ptr<InputComponent> getPlayerInputComponent();
	//virtual std::shared_ptr<VelocityComponent> getVelocityComponent();
	//virtual std::shared_ptr<PlayerStateComponent> getStateComponent();
	//std::shared_ptr<GraphicsComponent> getGraphicsComponent() { return graphics; }

	//Getters and Setters
	void setID(EntityID entId) { id = entId; }
	EntityID getID() const { return id; }
	void setPosition(float x, float y) ;
	Vector2f getPosition();
	EntityType getEntityType() const { return type; }
	SpriteSheet* getSpriteSheet() { return graphics->getSpriteSheet(); }
	Bitmask getComponentSet() { return componentSet; }
	bool isSpriteSheetEntity() const { return isSpriteSheet; }
	
	// X.C  Add two helper functions. One that returns the value of the deleted flag, another one that 
	//      "deletes" the entity by setting this flag to true. (Q: one of this functions should be "const", which one?).
	bool isDeleted() const { return deleted; }
	bool hasComponent(Bitmask mask) const { return componentSet.contains(mask); }
	void markDeleted() { deleted = true; }

	// <FEEDBACK> These pointers should be private, not public.
	std::shared_ptr<PositionComponent> position;
	std::shared_ptr<GraphicsComponent> graphics;
	std::shared_ptr<ColliderComponent> collider;

	//std::shared_ptr<ColliderComponent> getColliderComponent() { return collider; }

protected:

	EntityType type;
	EntityID id;

	Bitmask componentSet;
	bool isSpriteSheet;

	// X.A Add a bool member variable "deleted" to this class.
	bool deleted;
	std::map<ComponentID, std::shared_ptr<Component>> mapComponent;
};