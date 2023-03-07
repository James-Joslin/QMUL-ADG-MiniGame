#include "../../include/components/InputComponent.h"
#include "../../include/core/Game.h"
#include "../../include/core/InputHandler.h"
#include "../../include/core/Command.h"

#include <memory>


PlayerInputComponent::PlayerInputComponent()
{
	playerInputPointer = std::make_unique<PlayerInputHandler>();
}

void PlayerInputComponent::update(Game& game) 
{
	game.getPlayer()->setVelocity(Vector2f(0, 0));
	for (auto pointer : playerInputPointer->handleInput())
	{
		if (pointer)
		{
			// handle non-null pointer case
			pointer->execute(game);
		}
	}
}