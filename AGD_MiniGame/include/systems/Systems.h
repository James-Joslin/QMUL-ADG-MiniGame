#pragma once
#include "../utils/Bitmask.h"
#include "../core/Game.h"
#include <stdexcept>



class System
{
public:
	virtual void update(Entity*, Game*, float) = 0;
	bool validate(Entity* entity) { entity->hasComponent(entity->getComponentSet()); }

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
	void update(Entity* entity, Game* game, float elapsedTime) override
	{
		std::shared_ptr<TTLComponent> ttl = entity->getTTLComponent();

		if (ttl)
		{
			ttl->decrementTTL();
			if (ttl->getTTL() <= 0)
			{
				entity->markDeleted();
			}
		}
		else
		{
			std::exception("Null pointer raised for ttl component");
		}
	}



};