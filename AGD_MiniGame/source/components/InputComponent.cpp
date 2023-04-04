#include "../../include/components/InputComponent.h"
#include "../../include/core/Game.h"
#include "../../include/core/InputHandler.h"
#include "../../include/core/Command.h"

#include <memory>


PlayerInputComponent::PlayerInputComponent()
{
	playerInput = std::make_unique<PlayerInputHandler>();
}

void PlayerInputComponent::update(Game& game) 
{
	auto v = game.getPlayer()->getVelocityComp();
	v->setVelocityDirection(0.f, 0.f);

	//game.getPlayer()->setVelocity(Vector2f(0, 0));
	for (auto pointer : playerInput->handleInput())
	{
		//<FEEDBACK> This should never be the case, as you are not adding nullptr to the vector of the command pointers.
		//<CORRECTED> Removed nullptr if statement check.
		pointer->execute(game);
	}
}