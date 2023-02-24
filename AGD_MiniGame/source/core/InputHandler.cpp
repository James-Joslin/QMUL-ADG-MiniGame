#include "../../include/core/InputHandler.h"
#include "../../include/core/Command.h"
#include <SFML/Graphics.hpp>


InputHandler::InputHandler()
{
	pausePointer = std::make_shared<PauseCommand>();
}

PlayerInputHandler::PlayerInputHandler()
{
    rightPointer = std::make_shared<MoveRightCommand>();
}

std::shared_ptr<Command> InputHandler::handleInput()
{
    static bool isEscapePressed = false;

    if (sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        if (!isEscapePressed)
        {
            isEscapePressed = true;
            return pausePointer;
        }
    }
    else
    {
        isEscapePressed = false;
    }
    return nullptr;
}

std::shared_ptr<Command> PlayerInputHandler::handleInput()
{
    if (sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        return rightPointer;
    }
}