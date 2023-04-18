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
	std::shared_ptr<PlayerStateComponent> state = std::dynamic_pointer_cast<PlayerStateComponent>(game.getPlayer()->getComponent(ComponentID::STATE));
	state->setAttacking(true);
}

void FireCommand::execute(Game& game)
{
	std::shared_ptr<PlayerStateComponent> state = std::dynamic_pointer_cast<PlayerStateComponent>(game.getPlayer()->getComponent(ComponentID::STATE));
	state->setShouting(true);
}
