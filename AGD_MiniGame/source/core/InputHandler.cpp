#include "../../include/core/InputHandler.h"
#include <SFML/Graphics.hpp>

InputHandler::InputHandler()
{
	pausePointer = std::make_shared<Command>();
}

std::shared_ptr<Command> InputHandler::handleInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		return pausePointer;
	}
}