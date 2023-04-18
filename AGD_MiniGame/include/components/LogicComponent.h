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
	PlayerStateComponent(
		bool _attacking,
		bool _shouting,
		int _maxWood,
		int _wood,
		float _fireSpeed,
		float _shootCooldown,
		int _shootingCost,
		float _shootCooldownTime) :
		attacking{ _attacking },
		shouting{ _shouting },
		maxWood{ _maxWood },
		wood{ _wood },
		fireSpeed{ _fireSpeed },
		shootCooldown{ _shootCooldown },
		shootingCost{ _shootingCost },
		shootCooldownTime{ _shootCooldownTime } {};

	void update(Entity& entity, Game* game, float elapsed) override;
	
	void addWood(int w);

	std::shared_ptr<Fire> createFire(Entity*) const;
	ComponentID getID() { return ComponentID::STATE; }

	bool isAttacking() const { return attacking; }
	void setAttacking(bool at) { attacking = at; }

	bool isShouting() const { return shouting; }
	void setShouting(bool sh) { shouting = sh; }

	void setAttacking(bool at) { attacking = at; }

	void setShouting(bool sh) { shouting = sh; }

	bool isAttacking() const { return attacking; }

	bool isShouting() const { return shouting; }

private:
	bool attacking;
	bool shouting;
	int wood;
	const int maxWood;
	const float fireSpeed;
	float shootCooldown;
	const int shootingCost;
	const float shootCooldownTime;
};