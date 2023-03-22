#pragma once
#include <memory>
#include "Components.h"

class VelocityComponent;
class Entity;
class Game;
class Fire;

class LogicComponent : public Component
{
public:
	~LogicComponent() {};
	virtual void update(Entity& entity, Game* game, float elapsed) = 0;
};

class PlayerStateComponent : public LogicComponent
{
public:
	void update(Entity& entity, Game* game, float elapsed) override;
	
	void addWood(Entity& entity, int w);

	std::shared_ptr<Fire> createFire(Entity*) const;
	ComponentID getID() { return ComponentID::STATE; }

private:

	bool attacking{ false };
	bool shouting{ false };
	int wood{ 100 };
	float shootCooldown{ 0 };
	float fireSpeed = 200.f;
};