#include <memory>
#include "Components.h"

class Game;
class PlayerInputHandler;

class InputComponent : public Component
{
public:
	virtual ~InputComponent() {};
	virtual void update(Game*) = 0;
	virtual std::shared_ptr<PlayerInputHandler> getPlayerInputHander() = 0;

};

class PlayerInputComponent : public InputComponent
{
public:
	PlayerInputComponent();
	void update(Game*) override;
	
	ComponentID getID() override { return ComponentID::INPUT; }

	std::shared_ptr<PlayerInputHandler> getPlayerInputHander() override { return playerInput; }


private:
	std::shared_ptr<PlayerInputHandler> playerInput;

};