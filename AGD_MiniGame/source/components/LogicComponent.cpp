#include "../../include/components/LogicComponent.h"
#include "../../include/entities/Entity.h"
#include "../../include/core/Game.h"
#include "../../include/entities/Player.h"
#include "../../include/entities/Fire.h"

void PlayerStateComponent::update(Entity& entity, Game* game, float elapsed)
{	
	if (entity.getEntityType() == EntityType::PLAYER)
	{
		Player* player = dynamic_cast<Player*>(&entity);
		if (player != nullptr)
		{
			attacking = player->isAttacking();
			shouting = player->isShouting();

			if (player->getVelocityComp()->getVelocityDirection().x > 0)
			{
				player->graphicsPointer->setAnimation("Walk", true, true);
				player->graphicsPointer->setSpriteDirection(Direction::Right);
			}

			if (player->getVelocityComp()->getVelocityDirection().y > 0)
			{
				player->graphicsPointer->setAnimation("Walk", true, true);
			}

			if (player->getVelocityComp()->getVelocityDirection().x < 0)
			{
				player->graphicsPointer->setAnimation("Walk", true, true);
				player->graphicsPointer->setSpriteDirection(Direction::Left);
			}

			if (player->getVelocityComp()->getVelocityDirection().y < 0)
			{
				player->graphicsPointer->setAnimation("Walk", true, true);
			}

			if (player->getVelocityComp()->getVelocityDirection().x == 0 && player->getVelocityComp()->getVelocityDirection().y == 0 && !attacking && !shouting)
			{
				player->graphicsPointer->setAnimation("Idle", true, true);
			}

			if (attacking)
			{
				player->graphicsPointer->setAnimation("Attack", true, false);
			}

			if (shouting)
			{
				player->graphicsPointer->setAnimation("Shout", true, false);
			}

			// Logic for shooting a fireball
			if (shootCooldown > 0)
			{
				shootCooldown = shootCooldown - elapsed;
			}
			if
			(
				shouting && player->graphicsPointer->getSpriteSheet()->getCurrentAnim()->isInAction() && wood >= player->shootingCost && shootCooldown <= 0
			)
			{
				game->addEntity(
					player->createFire()
				);
				wood = wood - player->shootingCost;
				shootCooldown = player->shootCooldownTime;
			}
			if (!player->getSpriteSheet()->getCurrentAnim()->isPlaying())
			{
				player->setAttacking(false);
				player->setShouting(false);
			}
		}
	}
}

void PlayerStateComponent::addWood(Entity& entity, int w)
{
	Player* player = dynamic_cast<Player*>(&entity);
	if (player != nullptr)
	{
		wood += w;
		if (wood > player->maxWood) wood = player->maxWood;
		if (wood < 0) wood = 0;
	}
}