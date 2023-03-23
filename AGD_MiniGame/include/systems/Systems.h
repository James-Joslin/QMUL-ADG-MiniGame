#pragma once
#include "../utils/Bitmask.h"
#include "../../include/entities/Entity.h"

class Game;

class System
{
public:
	virtual void update(Entity*, Game*, float) = 0;
	bool validate(Entity* entity) { return entity->hasComponent(entity->getComponentSet()); }

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