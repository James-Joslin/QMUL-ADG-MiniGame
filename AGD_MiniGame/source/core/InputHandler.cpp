#include "../../include/core/InputHandler.h"
#include "../../include/core/Command.h"
#include <SFML/Graphics.hpp>


InputHandler::InputHandler()
{
	pausePointer = std::make_shared<PauseCommand>();
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