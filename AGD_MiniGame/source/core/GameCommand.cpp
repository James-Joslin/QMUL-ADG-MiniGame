#include "../../include/core/Command.h"

void PauseCommand::execute(Game& game)
{
	game.togglePause();
}