#include "../../include/core/Command.h"
#include "../../include/core/Game.h"
#include <iostream>

void MoveRightCommand::execute(Game& game)
{
	game.getPlayer()->setVelocityX(1.f);
}

void MoveLeftCommand::execute(Game& game)
{
	game.getPlayer()->setVelocityX(-1.f);
}

void MoveUpCommand::execute(Game& game)
{
	game.getPlayer()->setVelocityY(-1.f);
}

void MoveDownCommand::execute(Game& game)
{
	game.getPlayer()->setVelocityY(1.f);
}
