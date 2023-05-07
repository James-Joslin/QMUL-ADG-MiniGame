#include "../../include/core/Command.h"
#include "../../include/core/Game.h"
#include <iostream>
#include <cmath>

#define PI 3.14159265358979323846

void MoveRightCommand::execute(Game& game)
{
	//if (game.isMouse()) return;
	std::shared_ptr<VelocityComponent> velocity = std::dynamic_pointer_cast<VelocityComponent>(game.getPlayer()->getComponent(ComponentID::VELOCITY));
	velocity->setVelocityDirection(1.f, velocity->getVelocityDirection().y);
}

void MoveLeftCommand::execute(Game& game)
{
	//if (game.isMouse()) return;
	std::shared_ptr<VelocityComponent> velocity = std::dynamic_pointer_cast<VelocityComponent>(game.getPlayer()->getComponent(ComponentID::VELOCITY));
	velocity->setVelocityDirection(-1.f, velocity->getVelocityDirection().y);
}

void MoveUpCommand::execute(Game& game)
{
	//if (game.isMouse()) return;
	std::shared_ptr<VelocityComponent> velocity = std::dynamic_pointer_cast<VelocityComponent>(game.getPlayer()->getComponent(ComponentID::VELOCITY));
	velocity->setVelocityDirection(velocity->getVelocityDirection().x, -1.f);
}

void MoveDownCommand::execute(Game& game)
{
	//if (game.isMouse()) return;
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

void ClickCommand::execute(Game& game)
{
	if (game.getCurrentControl() == 2)
	{
		std::shared_ptr<PositionComponent> position = std::dynamic_pointer_cast<PositionComponent>(game.getPlayer()->getComponent(ComponentID::POSITION));
		std::shared_ptr<VelocityComponent> velocity = std::dynamic_pointer_cast<VelocityComponent>(game.getPlayer()->getComponent(ComponentID::VELOCITY));

		float target_x = sf::Mouse().getPosition(game.getWindow()->getWindow()).x - 50.f;
		float target_y = sf::Mouse().getPosition(game.getWindow()->getWindow()).y - 80.f;

		float player_x = position->getPosition().x;
		float player_y = position->getPosition().y;

		float movement_x = target_x - player_x;
		float movement_y = target_y - player_y;

		auto movementSystem = std::dynamic_pointer_cast<MovementSystem>(game.getLogicSystem()[2]);
		movementSystem->setTargetX(target_x);
		movementSystem->setTargetY(target_y);
		movementSystem->setMovementX(movement_x);
		movementSystem->setMovementY(movement_y);
	}
}
