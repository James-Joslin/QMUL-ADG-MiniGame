#pragma once
#include <memory>

class VelocityComponent;
class Entity;
class Game;
class Fire;

class LogicComponent
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
		float _fireSpeed) :
		attacking{ _attacking },
		shouting{ _shouting },
		maxWood{ _maxWood },
		wood{ _wood },
		fireSpeed{ _fireSpeed } {};

	void update(Entity& entity, Game* game, float elapsed) override;
	
	void addWood(int w);

	std::shared_ptr<Fire> createFire(Entity*) const;

	void setAttacking(bool at) { attacking = at; }

	void setShouting(bool sh) { shouting = sh; }

	bool isAttacking() const { return attacking; }

	bool isShouting() const { return shouting; }

private:

	bool attacking;
	bool shouting;
	int wood;
	int maxWood;
	float fireSpeed;
	float shootCooldown{ 0 };
};