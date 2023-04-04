#include <memory>

class Game;
class PlayerInputHandler;

class InputComponent
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

private:
	std::unique_ptr<PlayerInputHandler> playerInput;

};