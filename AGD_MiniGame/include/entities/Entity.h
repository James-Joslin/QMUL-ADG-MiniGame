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

enum class ArchetypeID;

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
	virtual void init(const std::string& textureFile, float scale, std::shared_ptr<GraphicsComponent> _graphics, ArchetypeID _archetypeID);
	void initSpriteSheet(const std::string& spriteSheetFile, ArchetypeID _archetypeID);
	void addComponent(std::shared_ptr<Component> c);
	std::shared_ptr<Component> getComponent(ComponentID id) { return mapComponent[id]; }
	void setID(EntityID entId) { id = entId; }
	EntityID getID() const { return id; }
	void setPosition(float x, float y) ;
	Vector2f getPosition();
	EntityType getEntityType() const { return type; }
	Bitmask getComponentSet() { return componentSet; }
	std::shared_ptr<PositionComponent> getPositionComponent() { return position; }
	std::shared_ptr<GraphicsComponent> getGraphicsComponent() { return graphics; }
	bool isDeleted() const { return deleted; }
	bool hasComponent(Bitmask mask) const { return componentSet.contains(mask); }
	void markDeleted() { deleted = true; }


	virtual std::shared_ptr<ColliderComponent> getColliderComponent();

	void setArchetypeID(ArchetypeID _archetypeID);
	ArchetypeID getArchetypeID() const;


	std::string typeToString(ArchetypeID _type); // was used to debug whether the archetypes were being assigned correctly


protected:

	EntityType type;
	EntityID id;

	Bitmask componentSet;
	bool isSpriteSheet;

	// X.A Add a bool member variable "deleted" to this class.
	bool deleted;
	std::map<ComponentID, std::shared_ptr<Component>> mapComponent;

	// <FEEDBACK> These pointers should be private, not public.
	// <CORRECTED> Pointers moved to protected, created getters for all three pointers.
	std::shared_ptr<PositionComponent> position;
	std::shared_ptr<GraphicsComponent> graphics;
	std::shared_ptr<ColliderComponent> collider;

	ArchetypeID archetypeID;
};