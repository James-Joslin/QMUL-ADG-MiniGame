#pragma once
#include "Game.h" // forward declaration?

class Command
{
public:
	Command();
	virtual ~Command();
	virtual void execute(Game& game);
};

class PauseCommand : public Command
{
public:
	virtual void execute(Game& game) override;
};