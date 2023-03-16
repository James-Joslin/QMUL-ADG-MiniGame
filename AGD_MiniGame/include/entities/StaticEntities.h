#pragma once
#include "Entity.h"
#include "../../include/components/PositionComponent.h"

class GameComponent;
class GraphicsComponent;

class Potion : public Entity
{
public:
	Potion() : Entity(EntityType::POTION) {}
	~Potion() {}

	void init(const std::string& textureFile, float scale, std::shared_ptr<GraphicsComponent> _graphicsPointer) override
	{
		// III.C (1/2) Call the init() function in Entity to initalize this object
		Entity::init(textureFile, scale, _graphicsPointer);
		// VIII.C (1/2) Set the top left and bottom right corners of the bounding box for this entity.
		Vector2f bboxLocation = position->getPosition();
		boundingBox.setTopLeft(
			bboxLocation
		);
		boundingBox.setBottomRight(
			Vector2f(
				(bboxLocation.x + bboxSize.x),
				(bboxLocation.y + bboxSize.y)
			)
		);
	}

	// virtual void update(Game* game, float elapsed = 1.0f) override { }

	int getHealth() const { return potionHealth; }

protected:
	const int potionHealth = 10;
};


class Log : public Entity
{
public:
	Log() : Entity(EntityType::LOG) {}
	~Log() {}

	void init(const std::string& textureFile, float scale, std::shared_ptr<GraphicsComponent> _graphicsPointer) override
	{
		// III.C (2/2) Call the init() function in Entity to initalize this object
		Entity::init(textureFile, scale, _graphicsPointer);
		// VIII.C (2/2) Set the top left and bottom right corners of the bounding box for this entity.
		Vector2f bboxLocation = position->getPosition();
		boundingBox.setTopLeft(
			bboxLocation
		);
		boundingBox.setBottomRight(
			Vector2f(
				(bboxLocation.x + bboxSize.x),
				(bboxLocation.y + bboxSize.y)
			)
		);
	}

	// virtual void update(Game* game, float elapsed = 1.0f) override {}

	int getWood() const { return woodAdded; }

protected:
	const int woodAdded = 15;
};