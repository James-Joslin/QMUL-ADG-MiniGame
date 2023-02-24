#include "../../include/core/Command.h"
#include "../../include/core/Game.h"
#include <iostream>

void MoveRightCommand::execute(Game& game)
{
	game.getPlayer()->setVelocityX(1.0f);
	std::cout << "hello" << std::endl;
	std::cout << game.getPlayer()->getVelocity().x << std::endl;
}

