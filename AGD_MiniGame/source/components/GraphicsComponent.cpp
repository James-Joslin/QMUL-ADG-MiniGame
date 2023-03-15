#include "../../include/components/GraphicsComponent.h"
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
	throw std::invalid_argument("You are trying to initialise an object that requires a sprite sheet with an animated sprite sheet");
}

// Initialising sprite sheets
void SpriteGraphics::initSpriteSheet(const std::string& spriteSheetFile)
{
	throw std::invalid_argument("You are trying to initialise an object that requires a spritesheet sheet with a sprite");
}

void SpriteSheetGraphics::initSpriteSheet(const std::string& spriteSheetFile)
{
	spriteSheet.loadSheet(spriteSheetFile);
	isSpriteSheet = true;
	spriteSheet.setAnimation("Idle", true, true);
}

