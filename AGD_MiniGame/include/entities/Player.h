#pragma once
#include "Entity.h"
#include "../components/HealthComponent.h"
#include "../components/VelocityComponent.h"
#include "../components/LogicComponent.h"
#include "../systems/Subject.h"

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

	/*std::shared_ptr<InputComponent> getPlayerInputComponent() override
	{
		return playerInput;
	}*/

	/*std::shared_ptr<VelocityComponent> getVelocityComponent() override
	{
		return velocity; 
	}*/
	//std::shared_ptr<PlayerStateComponent> getStateComponent() override
	//{
	//	return state;
	//}

//	void handleInput(Game& game);

	bool isAttacking() const { return attacking; }
	void setAttacking(bool at) { attacking = at; }

	bool isShouting() const { return shouting; }
	void setShouting(bool sh) { shouting = sh; }

	std::shared_ptr<HealthComponent> getHealthComp() { return healthComponent; }
	//std::shared_ptr<VelocityComponent> getVelocityComp() { return velocity; }

//	std::shared_ptr<InputComponent> getPlayerInput() { return playerInput; }

	int getWood() const { return wood; }
	//void addWood(int w);

	bool hasSpriteSheet() const { return isSpriteSheet; }

	void positionSprite(int row, int col, int spriteWH, float tileScale);

	void setGraphicsPointer(std::shared_ptr<GraphicsComponent> _graphics) { 
		addComponent(_graphics);
		graphics = _graphics; 
	}

	bool intersects(Entity& other);


	// std::shared_ptr<Fire> createFire() const;

	Subject& getPotionCollected() { return potionCollected; }
	Subject& getShoutTriggered() { return shoutTriggered; }
	void collectPotion();
	void shoutTrigger();

private:


	bool attacking;
	bool shouting;
	int wood;
	float shootCooldown;

	// VI.A (1/2): Declare a unique pointer to a player input handler.
	//std::unique_ptr<PlayerInputHandler> playerInputPointer;
	std::shared_ptr<InputComponent> playerInput;
	std::shared_ptr<HealthComponent> healthComponent;
	std::shared_ptr<VelocityComponent> velocity;
	std::shared_ptr<PlayerStateComponent> state;

	Subject potionCollected;
	Subject shoutTriggered;
};

