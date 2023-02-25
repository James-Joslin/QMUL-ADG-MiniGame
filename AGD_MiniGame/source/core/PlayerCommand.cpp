#include "../../include/core/Command.h"
#include "../../include/core/Game.h"
#include <iostream>

void MoveRightCommand::execute(Game& game)
{
	if (game.getPlayer()->isAttacking() || game.getPlayer()->isShouting()) return;
	game.getPlayer()->setVelocityX(1.f);
}

void MoveLeftCommand::execute(Game& game)
{
	if (game.getPlayer()->isAttacking() || game.getPlayer()->isShouting()) return;
	game.getPlayer()->setVelocityX(-1.f);
}

void MoveUpCommand::execute(Game& game)
{
	if (game.getPlayer()->isAttacking() || game.getPlayer()->isShouting()) return;
	game.getPlayer()->setVelocityY(-1.f);
}

void MoveDownCommand::execute(Game& game)
{
	if (game.getPlayer()->isAttacking() || game.getPlayer()->isShouting()) return;
	game.getPlayer()->setVelocityY(1.f);
}

void AttackCommand::execute(Game& game)
{
	if (game.getPlayer()->isAttacking() || game.getPlayer()->isShouting()) return;
	game.getPlayer()->setAttacking(true);
}

void FireCommand::execute(Game& game)
{
	if (game.getPlayer()->isAttacking() || game.getPlayer()->isShouting()) return;
	game.getPlayer()->setShouting(true);
}
