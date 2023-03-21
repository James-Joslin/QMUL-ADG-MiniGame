#include "../../include/core/Command.h"
#include "../../include/core/Game.h"
#include <iostream>

void MoveRightCommand::execute(Game& game)
{
	// <FEEDBACK> This check is not needed - movement should continue even if you attack or shout
	//			  Same applies to all movements.
	// <Corrected> Removed if statements preventing movement when animations are playing 
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

void AttackCommand::execute(Game& game)
{
	game.getPlayer()->setAttacking(true);
}

void FireCommand::execute(Game& game)
{
	game.getPlayer()->setShouting(true);
}
