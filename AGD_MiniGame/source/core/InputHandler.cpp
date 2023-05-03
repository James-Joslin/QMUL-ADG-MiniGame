#include "../../include/core/InputHandler.h"
#include "../../include/core/Command.h"
#include <SFML/Graphics.hpp>
#include <iostream>

InputHandler::InputHandler()
{
	pause = std::make_shared<PauseCommand>();
    enter = std::make_shared<SwitchCommand>();
}

PlayerInputHandler::PlayerInputHandler()
{ 
    right = std::make_shared<MoveRightCommand>();
    left = std::make_shared<MoveLeftCommand>();
    up = std::make_shared<MoveUpCommand>();
    down = std::make_shared<MoveDownCommand>();
    attack = std::make_shared<AttackCommand>();
    fire = std::make_shared<FireCommand>();
    click = std::make_shared <ClickCommand>();  
}

std::shared_ptr<Command> InputHandler::handleInput()
{
    static bool isEscapePressed = false;
    static bool isEnterPressed = false;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        if (!isEscapePressed)
        {
            isEscapePressed = true;
            return pause;
        }
    }
    else
    {
        isEscapePressed = false;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
    {
        if (!isEnterPressed)
        {
            isEnterPressed = true;
            return enter;
        }
    }
    else
    {
        isEnterPressed = false;
    }
    
    return nullptr;
}

std::vector <std::shared_ptr<Command>> PlayerInputHandler::handleInput()
{
    arrayCommand.clear();

    if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
    {
        arrayCommand.push_back(click);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        arrayCommand.push_back(right);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        arrayCommand.push_back(left);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        arrayCommand.push_back(up);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        arrayCommand.push_back(down);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        arrayCommand.push_back(attack);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
    {
        arrayCommand.push_back(fire);
    }
    return arrayCommand;
}