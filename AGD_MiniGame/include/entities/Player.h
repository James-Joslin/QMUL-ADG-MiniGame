#pragma once
#include "Entity.h"
#include "../components/HealthComponent.h"
#include "../components/VelocityComponent.h"
#include "../components/LogicComponent.h"

class Fire;
class InputComponent;
class LogicComponent;

// VI.A (2/2): Add a forward declaration to the class PlayerInputHandler
class PlayerInputHandler;

class Player :  public Entity
{
public:

	const float playerSpeed = 100.f;
	const int startingHealth = 60;
	const int maxHealth = 100;
	const int maxWood = 100;
	const int shootingCost = 20;
	const float fireSpeed = 200.f;
	const float shootCooldownTime = 3.f; //in seconds

	Player();
	~Player();

	virtual void update(Game* game, float elapsed = 1.0f) override;

	void handleInput(Game& game);

	bool isAttacking() const { return attacking; }
	void setAttacking(bool at) { attacking = at; }

	bool isShouting() const { return shouting; }
	void setShouting(bool sh) { shouting = sh; }

	std::shared_ptr<HealthComponent> getHealthComp() { return healthComponentPointer; }
	std::shared_ptr<VelocityComponent> getVelocityComp() { return velocity; }

	int getWood() const { return wood; }
	void addWood(int w);

	bool hasSpriteSheet() const { return isSpriteSheet; }

	void positionSprite(int row, int col, int spriteWH, float tileScale);

	void setGraphicsPointer(std::shared_ptr<GraphicsComponent> _graphicsPointer) { graphicsPointer = _graphicsPointer; }

	bool intersects(Entity& other) { return collider->intersects(other.getColliderComponent().get()->getBoundingBox()); }


	std::shared_ptr<Fire> createFire() const;

private:


	bool attacking;
	bool shouting;
	int wood;
	float shootCooldown;

	// VI.A (1/2): Declare a unique pointer to a player input handler.
	//std::unique_ptr<PlayerInputHandler> playerInputPointer;
	std::unique_ptr<InputComponent> playerInputPointer;
	std::shared_ptr<HealthComponent> healthComponentPointer;
	std::shared_ptr<VelocityComponent> velocity;
	std::unique_ptr<PlayerStateComponent> state;

};

