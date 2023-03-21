#include <memory>
#include "Components.h"

class Game;
class PlayerInputHandler;

class InputComponent : public Component
{
public:
	virtual ~InputComponent() {};
	virtual void update(Game&) = 0;

};

class PlayerInputComponent : public InputComponent
{
public:
	PlayerInputComponent();
	void update(Game&) override;
	
	ComponentID getID() { return ComponentID::INPUT; }


private:
	std::unique_ptr<PlayerInputHandler> playerInput;

};