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

class MoveLeftCommand : public Command
{
public:
	virtual void execute(Game& game) override;
};

class MoveUpCommand : public Command
{
public:
	virtual void execute(Game& game) override;
};

class MoveDownCommand : public Command
{
public:
	virtual void execute(Game& game) override;
};

class AttackCommand : public Command
{
public:
	virtual void execute(Game& game) override;
};

class FireCommand : public Command
{
public:
	virtual void execute(Game& game) override;
};