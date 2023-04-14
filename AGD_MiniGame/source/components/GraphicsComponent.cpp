#include "../../include/components/GraphicsComponent.h"
#include "../../include/graphics/Window.h"
#include "../../include/utils/Vector2.h"
#include <stdexcept>

// Initialising sprites
void SpriteGraphics::init(const std::string& textureFile, float scale)
{
	texture.loadFromFile(textureFile);
	sprite.setTexture(texture);
	sprite.setScale(scale, scale);
}

void SpriteSheetGraphics::init(const std::string& textureFile, float scale)
{
	throw std::exception("You are trying to initialise a sprite object with an animated sprite sheet");
}

// Initialising sprite sheets
void SpriteGraphics::initSpriteSheet(const std::string& spriteSheetFile)
{
	throw std::exception("You are trying to initialise an object that requires a spritesheet sheet as if it were a standard sprite");
}

void SpriteSheetGraphics::initSpriteSheet(const std::string& spriteSheetFile)
{
	spriteSheet.loadSheet(spriteSheetFile);
	isSpriteSheet = true;
	spriteSheet.setAnimation("Idle", true, true);
}

// <FEEDBACK> These draw() methods are never called (nor they should be). All is managed in the system. These can go.
// <CORRECTED> Draw() methods removed from cpp and header files.

void SpriteGraphics::setPosition(Vector2f position)
{
	sprite.setPosition(position.x, position.y);
}

void SpriteSheetGraphics::setPosition(Vector2f position)
{
	spriteSheet.getSprite().setPosition(position.x, position.y);
}

void SpriteSheetGraphics::setAnimation(const std::string &name, bool play, bool loop)
{
	spriteSheet.setAnimation(name, play, loop);
}

void SpriteSheetGraphics::setSpriteDirection(Direction direction)
{
	spriteSheet.setSpriteDirection(direction);
}

// <FEEDBACK> Same here: these update functions are not needed - logic is in the system now.
// <CORRECTED> Update() methods removed from cpp and header files.
