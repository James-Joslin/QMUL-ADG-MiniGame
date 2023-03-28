#pragma once
#include "../utils/Bitmask.h"
#include "../../include/entities/Entity.h"

class Game;

class System
{
public:
	virtual void update(Entity*, Game*, float) = 0;
	bool validate(Entity* entity) { return entity->hasComponent(componentMask); }

protected:
	Bitmask componentMask;

};

class TTLSystem : public System
{
public:
	TTLSystem()
	{
		componentMask.turnOnBit(static_cast<int>(ComponentID::TTL));
	}
	void update(Entity*, Game*, float) override;
};

class InputSystem : public System
{
public:
	InputSystem()
	{
		componentMask.turnOnBit(static_cast<int>(ComponentID::INPUT));
		componentMask.turnOnBit(static_cast<int>(ComponentID::POSITION));
	}
	void update(Entity*, Game*, float) override;
};

class MovementSystem : public System
{
public:
	MovementSystem()
	{
		componentMask.turnOnBit(static_cast<int>(ComponentID::POSITION));
		componentMask.turnOnBit(static_cast<int>(ComponentID::VELOCITY));
	}
	void update(Entity*, Game*, float) override;
};

class GraphicsSystem : public System
{
public:
	GraphicsSystem()
	{
		componentMask.turnOnBit(static_cast<int>(ComponentID::POSITION));
		componentMask.turnOnBit(static_cast<int>(ComponentID::GRAPHICS));
	}
	void update(Entity*, Game*, float) override;
};

class GameplaySystem : public System
{
public:
	GameplaySystem()
	{
		componentMask.turnOnBit(static_cast<int>(ComponentID::STATE));
	}
	void update(Entity*, Game*, float) override;
};

class ColliderSystem : public System
{
public: 
	ColliderSystem()
	{
		componentMask.turnOnBit(static_cast<int>(ComponentID::POSITION));
		componentMask.turnOnBit(static_cast<int>(ComponentID::COLLIDER));
	}
	void update(Entity*, Game*, float) override;
};