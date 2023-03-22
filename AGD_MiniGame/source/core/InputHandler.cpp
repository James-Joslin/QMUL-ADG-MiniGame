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
    attackPointer = std::make_shared<AttackCommand>();
    firePointer = std::make_shared<FireCommand>();
}

std::shared_ptr<Command> InputHandler::handleInput()
{
    static bool isEscapePressed = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
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

std::vector <std::shared_ptr<Command>> PlayerInputHandler::handleInput()
{
    arrayCommand.clear();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        arrayCommand.push_back(rightPointer);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        arrayCommand.push_back(leftPointer);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        arrayCommand.push_back(upPointer);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        arrayCommand.push_back(downPointer);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        arrayCommand.push_back(attackPointer);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
    {
        arrayCommand.push_back(firePointer);
    }
    //arrayCommand.push_back(nullptr);
    return arrayCommand;
}