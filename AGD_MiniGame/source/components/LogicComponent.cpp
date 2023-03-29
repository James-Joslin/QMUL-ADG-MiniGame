#include "../../include/components/LogicComponent.h"
#include "../../include/components/VelocityComponent.h"
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
				if (velocity->getVelocityDirection().x > 0)
				{
					player->graphics->setAnimation("Walk", true, true);
					player->graphics->setSpriteDirection(Direction::Right);
				}

				else if (velocity->getVelocityDirection().x < 0)
				{
					player->graphics->setAnimation("Walk", true, true);
					player->graphics->setSpriteDirection(Direction::Left);
				}

				else if (velocity->getVelocityDirection().x == 0 && velocity->getVelocityDirection().y == 0 && !attacking && !shouting)
				{
					player->graphics->setAnimation("Idle", true, true);
				}

				else if (velocity->getVelocityDirection().y != 0)
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
				game->addEntity(createFire(player));
				wood = wood - player->shootingCost;
				shootCooldown = player->shootCooldownTime;
			}
			
			if (attacking && player->graphics->getSpriteSheet()->getCurrentAnim()->isPlaying() == false)
			{
				setAttacking(false);
			}
			if (shouting && player->graphics->getSpriteSheet()->getCurrentAnim()->isPlaying() == false)
			{
				setShouting(false);
			}
		}
	}
}

void PlayerStateComponent::addWood(Entity& entity, int w)
{
	wood += w;
	if (wood > maxWood) wood = maxWood;
	if (wood < 0) wood = 0;
	std::cout << "Collide with wood (Wood collected: " << w << ", Total Player Wood: " << wood << ")" << std::endl;
}

std::shared_ptr<Fire> PlayerStateComponent:: createFire(Entity* player) const
{
	auto fireEntity = std::make_shared<Fire>();
	
	Vector2f pos{ player->getPosition().x + player->graphics->getTextureSize().x * 0.5f, player->getPosition().y + player->graphics->getTextureSize().y * 0.5f};
	fireEntity->init("img/fire.png", 1.0f, std::make_shared<SpriteGraphics>());
	fireEntity->setPosition(pos.x, pos.y);
	Vector2f vel(fireSpeed, 0.f);
	if (player->graphics->getSpriteDirection() == Direction::Left) vel.x = vel.x * -1.0f;


	std::shared_ptr<VelocityComponent> velocity = std::dynamic_pointer_cast<VelocityComponent>(fireEntity->getComponent(ComponentID::VELOCITY));


	velocity->setVelocityDirection(vel.x, vel.y);

	return fireEntity;
}