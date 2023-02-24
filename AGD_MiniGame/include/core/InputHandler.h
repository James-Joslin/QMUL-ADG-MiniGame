#include <memory>

// forward declaration of Command
class Command;

class InputHandler
{
public:
	InputHandler();

	std::shared_ptr<Command> handleInput();

private:
	std::shared_ptr<Command> pausePointer;
};

class PlayerInputHandler
{
public:
	PlayerInputHandler();

	std::shared_ptr<Command> handleInput();

private:
	std::shared_ptr<Command> rightPointer;
	std::shared_ptr<Command> leftPointer;
	std::shared_ptr<Command> upPointer;
	std::shared_ptr<Command> downPointer;
};