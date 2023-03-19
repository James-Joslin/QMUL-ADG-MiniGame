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
	void update(Entity& entity, Game* game, float elapsed) override;
	void addWood(Entity& entity, int w);

private:

	bool attacking{ false };
	bool shouting{ false };
	int wood{ 0 };
	float shootCooldown{ 0 };
};