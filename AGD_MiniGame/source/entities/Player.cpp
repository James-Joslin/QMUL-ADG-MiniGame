#include "../../include/entities/Player.h"
#include "../../include/graphics/AnimBase.h"
#include "../../include/entities/Fire.h"
#include "../../include/core/Game.h"
#include "../../include/core/InputHandler.h"
#include "../../include/core/Command.h"
#include "../../include/components/InputComponent.h"
#include "../../include/components/PositionComponent.h"
#include "../../include/components/GraphicsComponent.h"
#include "../../include/components/LogicComponent.h"
#include <iostream>


Player::Player() : Entity(EntityType::PLAYER), attacking(false), shouting(false), wood(0), shootCooldown(0)
{
	// VI.B: Create the unique pointer to the PlayerInputHandler object
	playerInput = std::make_unique<PlayerInputComponent>();
	healthComponent = std::make_shared<HealthComponent>(startingHealth, maxHealth);
	velocity = std::make_shared<VelocityComponent>(playerSpeed);
	state = std::make_shared<PlayerStateComponent>(attacking, shouting, maxWood, wood, fireSpeed, shootCooldown, shootingCost, shootCooldownTime);
}

Player::~Player() {}

void Player::update(Game* game, float elapsed)
{
	// velocity update
	velocity->update(*this, elapsed);
	collider->update(getPosition()); // entitiy getPosition calls position-> getPosition
	graphics->update(game, elapsed, getPosition()); // hasn't been implemented yet
	state->update(*this, game, elapsed);
}

void Player::handleInput(Game& game)
{
	playerInput->update(game);
}

void Player::positionSprite(int row, int col, int spriteWH, float tileScale)
{
	sf::Vector2f scaleV2f = graphics->getSpriteScale();
	sf::Vector2i textureSize = graphics->getTextureSize();

	float x = col * spriteWH * tileScale;
	float y = (row)*spriteWH * tileScale;
	float spriteSizeY = scaleV2f.y * textureSize.y;
	float cntrFactorY = ((spriteWH * tileScale) - spriteSizeY);	// to align to lower side of the tile.
	float cntrFactorX = cntrFactorY * 0.5f;						//to center horizontally

	setPosition(x + cntrFactorX, y + cntrFactorY);
	velocity->setVelocityDirection(0.f, 0.f);
}
