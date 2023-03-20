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

			if (attacking)
			{
				player->graphics->setAnimation("Attack", true, false);
			}

			else if (shouting)
			{
				player->graphics->setAnimation("Shout", true, false);
			}

			else
			{
				if (player->getVelocityComp()->getVelocityDirection().x > 0)
				{
					player->graphics->setAnimation("Walk", true, true);
					player->graphics->setSpriteDirection(Direction::Right);
				}

				else if (player->getVelocityComp()->getVelocityDirection().x < 0)
				{
					player->graphics->setAnimation("Walk", true, true);
					player->graphics->setSpriteDirection(Direction::Left);
				}

				else if (player->getVelocityComp()->getVelocityDirection().x == 0 && player->getVelocityComp()->getVelocityDirection().y == 0 && !attacking && !shouting)
				{
					player->graphics->setAnimation("Idle", true, true);
				}

				else if (player->getVelocityComp()->getVelocityDirection().y != 0)
				{
					player->graphics->setAnimation("Walk", true, true);
				}
			}

			if (shootCooldown > 0)
			{
				shootCooldown = shootCooldown - elapsed;
			}
			if (shouting && player->graphics->getSpriteSheet()->getCurrentAnim()->isInAction() && wood >= player->shootingCost && shootCooldown <= 0)
			{
				game->addEntity(player->createFire());
				wood = wood - player->shootingCost;
				shootCooldown = player->shootCooldownTime;
			}
			
			if (attacking && player->graphics->getSpriteSheet()->getCurrentAnim()->isPlaying() == false)
			{
				player->setAttacking(false);
			}
			if (shouting && player->graphics->getSpriteSheet()->getCurrentAnim()->isPlaying() == false)
			{
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