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

	//virtual void update(Game* game, float elapsed = 1.0f) override;

	std::shared_ptr<InputComponent> getInputComponent() 
	{
		return playerInput;
	}

	/*std::shared_ptr<VelocityComponent> getVelocityComponent() override
	{
		return velocity; 
	}*/
	//std::shared_ptr<PlayerStateComponent> getStateComponent() override
	//{
	//	return state;
	//}

//	void handleInput(Game& game);

	std::shared_ptr<HealthComponent> getHealthComp() { return healthComponent; }
	std::shared_ptr<VelocityComponent> getVelocityComp() { return velocity; }
	std::shared_ptr<PlayerStateComponent> getStateComp() { return state; }

	void positionSprite(int row, int col, int spriteWH, float tileScale);

	void setGraphicsPointer(std::shared_ptr<GraphicsComponent> _graphics) { 
		addComponent(_graphics);
		graphics = _graphics;
	}

	bool intersects(Entity& other);

	std::shared_ptr<ColliderComponent> getColliderComponent() override { return collider; }

private:

	bool attacking;
	bool shouting;
	int wood;
	float shootCooldown;

	// VI.A (1/2): Declare a unique pointer to a player input handler.
	std::shared_ptr<InputComponent> playerInput;
	std::shared_ptr<HealthComponent> healthComponent;
	std::shared_ptr<VelocityComponent> velocity;
	std::shared_ptr<PlayerStateComponent> state;
};

