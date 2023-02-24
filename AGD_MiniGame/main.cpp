#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "../core/Game.h"

void adaptiveLoop(Game& game, float& lastTime, float updateTarget = 0)
{
    float current = game.getElapsed().asSeconds();
    float elapsedSeconds = current - lastTime;

    // I.A: Three function calls for the game loop: handleInput, update and render.
    //    Update and Render are frame-dependent
    game.handleInput();
    game.update(elapsedSeconds);
    game.render(elapsedSeconds);

    // I.B: This loop is time-variable, set the game to sleep in order to get a 
    //      constant framerate.
    sf::sleep(sf::seconds(updateTarget - (game.getElapsed().asSeconds() - current)));

    // I.C: Calculate the current frame rate and set it to the game.
    int fps = (int) (1 / (game.getElapsed().asSeconds() - current));

    // I.D: Call the function game.setFPS(int) to inform the game about the current FPS. Print this value to console as well.
    //std::cout << "FPS: " << fps << " Elasped: " << elapsedSeconds << std::endl;
    game.setFPS(fps);

    lastTime = current;
}

int main(int argc, char** argv[])
{
    // Try to load the level:
    std::ifstream levelRead{ "levels/lvl0.txt" };
    if (!levelRead)
    {
        throw std::exception("File not found\n");
    }

    // Convert the read file into a vector of strings, one per line:
    std::vector<std::string> lines;
    while (levelRead)
    {
        std::string strInput;
        std::getline(levelRead, strInput);
        lines.emplace_back(strInput);
    }


    // Create and initalize the game.
    Game game;
    game.init(lines);

    // GAME LOOP (with an update target time at 60FPS)
    float updateTarget = 0.016f; //FPS: 60
    float lastTime = game.getElapsed().asSeconds();

    while (!game.getWindow()->isWindowDone())
    {
        //Adaptive loop to elapsed time, with a target update.
        adaptiveLoop(game, lastTime, updateTarget);
    }

    
    return 0;
}