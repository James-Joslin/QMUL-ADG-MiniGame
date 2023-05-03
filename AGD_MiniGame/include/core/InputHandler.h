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
	std::shared_ptr<Command> pause;
	std::shared_ptr<Command> enter;
	
};

class PlayerInputHandler
{
public:
	PlayerInputHandler();
	std::vector<std::shared_ptr<Command>> handleInput();
	std::vector<std::shared_ptr<Command>> arrayCommand;

private:

	std::shared_ptr<Command> click;
	std::shared_ptr<Command> right;
	std::shared_ptr<Command> left;
	std::shared_ptr<Command> up;
	std::shared_ptr<Command> down;
	std::shared_ptr<Command> attack;
	std::shared_ptr<Command> fire;
};