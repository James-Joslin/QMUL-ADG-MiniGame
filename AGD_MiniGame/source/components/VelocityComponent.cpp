#include "../../include/components/VelocityComponent.h"
#include "../../include/components/PositionComponent.h"
#include "../../include/entities/Player.h"
#include "../../include/entities/Fire.h"
#include <iostream>


void VelocityComponent::update(Entity& entity, float elapsedTime)
{
	if (entity.getEntityType() == EntityType::PLAYER)
	{

		Player& player = dynamic_cast<Player&>(entity);
		player.setPosition(player.getPosition().x + (getVelocityDirection().x * speed * elapsedTime),
			player.getPosition().y + (getVelocityDirection().y * speed * elapsedTime));
	}


	

	if (entity.getEntityType() == EntityType::FIRE)
	{
		Fire& fire = dynamic_cast<Fire&>(entity);
		fire.setPosition(fire.getPosition().x + (getVelocityDirection().x * speed * elapsedTime),
			fire.getPosition().y + (getVelocityDirection().y * speed * elapsedTime));
	}
	
	


	//std::cout << player.getVelocityComp()->getVelocityDirection().x << " " << player.getVelocityComp()->getVelocityDirection().y << std::endl;
		
	/*setPosition(
		position->getPosition().x + (velocity.x * speed * elapsed),
		position->getPosition().y + (velocity.y * speed * elapsed));*/

}