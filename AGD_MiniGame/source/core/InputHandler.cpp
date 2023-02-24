#include "../../include/core/InputHandler.h"
#include "../../include/core/Command.h"
#include <SFML/Graphics.hpp>
#include <iostream>

InputHandler::InputHandler()
{
	pausePointer = std::make_shared<PauseCommand>();
}

PlayerInputHandler::PlayerInputHandler()
{
    rightPointer = std::make_shared<MoveRightCommand>();
    leftPointer = std::make_shared<MoveLeftCommand>();
    upPointer = std::make_shared<MoveUpCommand>();
    downPointer = std::make_shared<MoveDownCommand>();
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
    if (sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        return leftPointer;
    }
    if (sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        return upPointer;
    }
    if (sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        return downPointer;
    }
}