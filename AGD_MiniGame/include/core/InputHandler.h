#include <memory>
#include <vector>

// forward declaration of Command
class Command;

class InputHandler
{
public:
	InputHandler();

	std::shared_ptr<Command> handleInput();

private:
	// <FEEDBACK> It is odd to name a variable "pointer". Kind of like calling a variable "pauseVariable". Avoid this (through the code, below as well).
	std::shared_ptr<Command> pausePointer;
};

class PlayerInputHandler
{
public:
	PlayerInputHandler();

	std::vector<std::shared_ptr<Command>> handleInput();

private:
	std::vector<std::shared_ptr<Command>> arrayCommand;
	std::shared_ptr<Command> rightPointer;
	std::shared_ptr<Command> leftPointer;
	std::shared_ptr<Command> upPointer;
	std::shared_ptr<Command> downPointer;
	std::shared_ptr<Command> attackPointer;
	std::shared_ptr<Command> firePointer;
};