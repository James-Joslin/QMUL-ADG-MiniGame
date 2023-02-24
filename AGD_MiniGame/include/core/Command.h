#pragma once

class Game;

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

class MoveRightCommand : public Command
{
public:
	virtual void execute(Game& game) override;
};