#include "../../include/entities/Player.h"
#include "../../include/graphics/AnimBase.h"
#include "../../include/entities/Fire.h"
#include "../../include/core/Game.h"
#include "../../include/core/InputHandler.h"
#include "../../include/core/Command.h"
#include "../../include/components/InputComponent.h"
#include "../../include/components/PositionComponent.h"
#include "../../include/components/GraphicsComponent.h"
#include <iostream>


Player::Player() : Entity(EntityType::PLAYER), attacking(false), shouting(false), wood(0), shootCooldown(0)
{
	// VI.B: Create the unique pointer to the PlayerInputHandler object
	playerInputPointer = std::make_unique<PlayerInputComponent>();
	healthComponentPointer = std::make_shared<HealthComponent>(startingHealth, maxHealth);
	velocity = std::make_shared<VelocityComponent>(playerSpeed);
}

Player::~Player() {}

void Player::update(Game* game, float elapsed)
{
	velocity->update(*this, elapsed);
		// VI.G Modify the code below to add the functionality to play the appropriate animations 
		//      and set the appropriate directions for movement depending on the  value of the
		//      velocity vector for moving up, down and left.


		// VI.F (1/2) If the X component of the velocity vector is positive, we're moving to the right.
		//            Set the animation of the spritesheet to "Walk". Mind the parameters required for the
		//			  animation: if it should start playing and if it should loop.
		//			  Additionally, you must also set the sprite direction (to Direction::Right) of the spritesheet.
	if (velocity->getVelocityDirection().x > 0)
	{
		graphicsPointer->setAnimation("Walk", true, true);
		graphicsPointer->setSpriteDirection(Direction::Right);
	}

	if (velocity->getVelocityDirection().y > 0)
	{
		graphicsPointer->setAnimation("Walk", true, true);
	}

	if (velocity->getVelocityDirection().x < 0)
	{
		graphicsPointer->setAnimation("Walk", true, true);
		graphicsPointer->setSpriteDirection(Direction::Left);
	}

	if (velocity->getVelocityDirection().y < 0)
	{
		graphicsPointer->setAnimation("Walk", true, true);
	}

	// VI.F (2/2) If the player is not moving, we must get back to playing the "Idle" animation.
	if (velocity->getVelocityDirection().x == 0 && velocity->getVelocityDirection().y == 0 && !attacking && !shouting)
	{
		graphicsPointer->setAnimation("Idle", true, true);
	}

	if (attacking)
	{
		graphicsPointer->setAnimation("Attack", true, true);
	}

	if (shouting)
	{
		graphicsPointer->setAnimation("Shout", true, true);
	}

	
	
	// IV.D (1/2) Call the function update in the base class to do the general update stuff that is common to all entities.
	Entity::update(game, elapsed);

	// XI.B (2/2):  Reduce the shoot cooldown counter by the elapsed time at every frame. 
	//              Only do this if shoot cooldown is > 0 (can you guess why?)
	if (shootCooldown > 0)
	{
		shootCooldown = shootCooldown - elapsed;
	}

	// XI.A: Create an Fire entity object (using Player::createFire()) and add it to the game (using Game::addEntity).
	//       Then, remove the shooting cost (Player::shootingCost) from the wood member variable of this class
	//       Finally, wrap the functionality below in an IF statement, so we only spawn fire when:
	//            1) We are playing the shouting animation
	//			  2) The animation is in one of the "in action" frames.
	//			  3) We have enough wood "ammunition" (variable wood and shootingCost)
	if (
		shouting && graphicsPointer->getSpriteSheet().getCurrentAnim()->isInAction() // graphics component - function for returning spritesheet animation?
		&& 
		wood >= shootingCost && shootCooldown <= 0
	)
	{
		game->addEntity(
			createFire()
		);
		wood = getWood() - shootingCost;
		
		// XI.B (1/2): Set the variable shootCooldown to the cooldown time (defined in shootCooldownTime).
		//        Add another condition to the shooting IF statement that only allows shoowing if shootCooldown <= 0.

		shootCooldown = shootCooldownTime;
	}

	// VII.B: If we are attacking but the current animation is no longer playing, set the attacking flag to false.
	//        The same needs to be done for "shouting".
	if (!graphicsPointer->getSpriteSheet().getCurrentAnim()->isPlaying())
	{
		setAttacking(false);
		setShouting(false);
	}
}


void Player::handleInput(Game& game)
{
	playerInputPointer->update(game);
}

std::shared_ptr<Fire> Player::createFire() const
{
	auto fireEntity = std::make_shared<Fire>();		

	Vector2f pos { position->getPosition().x + getTextureSize().x * 0.5f, position->getPosition().y + getTextureSize().y * 0.5f };
	fireEntity->init("img/fire.png", 1.0f, std::make_shared<SpriteGraphics>());
	fireEntity->setPosition(pos.x, pos.y);
	Vector2f vel(fireSpeed, 0.f);
	if (graphicsPointer->getSpriteSheet().getSpriteDirection() == Direction::Left) vel.x = vel.x * -1.0f;
	fireEntity->getVelocityPtr()->setVelocityDirection(vel.x, vel.y);

	return fireEntity;
}

void Player::addWood(int w)
{
	wood += w;
	if (wood > maxWood) wood = maxWood;
	if (wood < 0) wood = 0;
}


void Player::positionSprite(int row, int col, int spriteWH, float tileScale)
{
	sf::Vector2f scaleV2f = getSpriteScale();
	sf::Vector2i textureSize = getTextureSize();

	float x = col * spriteWH * tileScale;
	float y = (row)*spriteWH * tileScale;
	float spriteSizeY = scaleV2f.y * textureSize.y;
	float cntrFactorY = ((spriteWH * tileScale) - spriteSizeY);	// to align to lower side of the tile.
	float cntrFactorX = cntrFactorY * 0.5f;						//to center horizontally

	setPosition(x + cntrFactorX, y + cntrFactorY);
	velocity->setVelocityDirection(0.f, 0.f);
}
