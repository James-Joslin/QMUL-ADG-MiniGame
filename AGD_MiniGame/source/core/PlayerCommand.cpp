#include "../../include/core/Command.h"
#include "../../include/core/Game.h"
#include <iostream>

void MoveRightCommand::execute(Game& game)
{
	game.getPlayer()->getVelocityComp()->setVelocityDirection(1.f, game.getPlayer()->getVelocityComp()->getVelocityDirection().y);
}

void MoveLeftCommand::execute(Game& game)
{
	game.getPlayer()->getVelocityComp()->setVelocityDirection(-1.f, game.getPlayer()->getVelocityComp()->getVelocityDirection().y);
}

void MoveUpCommand::execute(Game& game)
{
	game.getPlayer()->getVelocityComp()->setVelocityDirection(game.getPlayer()->getVelocityComp()->getVelocityDirection().x, -1.f);
}

void MoveDownCommand::execute(Game& game)
{
	game.getPlayer()->getVelocityComp()->setVelocityDirection(game.getPlayer()->getVelocityComp()->getVelocityDirection().x, 1.f);
}

void AttackCommand::execute(Game& game)
{
	game.getPlayer()->setAttacking(true);
}

void FireCommand::execute(Game& game)
{
	game.getPlayer()->setShouting(true);
}
