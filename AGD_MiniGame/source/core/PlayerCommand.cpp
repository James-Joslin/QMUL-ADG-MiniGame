#include "../../include/core/Command.h"
#include "../../include/core/Game.h"
#include <iostream>

void MoveRightCommand::execute(Game& game)
{
	std::shared_ptr<VelocityComponent> velocity = std::dynamic_pointer_cast<VelocityComponent>(game.getPlayer()->getComponent(ComponentID::VELOCITY));
	velocity->setVelocityDirection(1.f, velocity->getVelocityDirection().y);
}

void MoveLeftCommand::execute(Game& game)
{
	std::shared_ptr<VelocityComponent> velocity = std::dynamic_pointer_cast<VelocityComponent>(game.getPlayer()->getComponent(ComponentID::VELOCITY));
	velocity->setVelocityDirection(-1.f, velocity->getVelocityDirection().y);
}

void MoveUpCommand::execute(Game& game)
{
	std::shared_ptr<VelocityComponent> velocity = std::dynamic_pointer_cast<VelocityComponent>(game.getPlayer()->getComponent(ComponentID::VELOCITY));
	velocity->setVelocityDirection(velocity->getVelocityDirection().x, -1.f);
}

void MoveDownCommand::execute(Game& game)
{
	std::shared_ptr<VelocityComponent> velocity = std::dynamic_pointer_cast<VelocityComponent>(game.getPlayer()->getComponent(ComponentID::VELOCITY));
	velocity->setVelocityDirection(velocity->getVelocityDirection().x, 1.f);
}

void AttackCommand::execute(Game& game)
{
	game.getPlayer()->setAttacking(true);
}

void FireCommand::execute(Game& game)
{
	game.getPlayer()->setShouting(true);
}
