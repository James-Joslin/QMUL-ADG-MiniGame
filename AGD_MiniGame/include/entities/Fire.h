#pragma once
#include "Entity.h"
#include "../components/TTLComponent.h"
#include "../components/VelocityComponent.h"

class Fire : public Entity
{
public:
	const int startTimeToLive = 150; //frames

	Fire();
	~Fire();

	//virtual void update(Game* game, float elapsed = 1.0f) override;

	/*std::shared_ptr<TTLComponent> getTTLComponent() override
	{
		return ttlPtr;
	}*/

	//std::shared_ptr<VelocityComponent> getVelocityComponent() override
	//{
	//	return velocityPtr;
	//}

	int getTTL() const { return ttlPtr->getTTL(); }

	//std::shared_ptr<VelocityComponent>getVelocityPtr() { return velocityPtr; }

private:

	std::shared_ptr<TTLComponent> ttlPtr;
	std::shared_ptr<VelocityComponent> velocityPtr;
};

