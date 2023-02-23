#pragma once
#include "Game.h"

class Command
{
public:
	virtual ~Command() {};
	virtual void execute(Game& game) = 0;
};

class PauseCommand : public Command
{
public:
	virtual void execute(Game& game) override;
};
