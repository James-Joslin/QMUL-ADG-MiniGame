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
	spriteSheet.setAnimation("Idle", true, true);
}

//<FEEDBACK> 
void SpriteGraphics::draw(Window* window)
{
	window->draw(sprite);
}

void SpriteSheetGraphics::draw(Window* window)
{
	//<FEEDBACK> In which case isSpriteSheet is going to be false in this class?
	// You don't need this variable
	//<CORRECTED> Removed if statement
	window->draw(spriteSheet.getSprite());
	//<FEEDBACK> Be more descriptive in your error message
	//<CORRECTED> Feedback noted, however error message was not neccessary and therefore removed
}

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

void SpriteSheetGraphics::update(Game* game, float elapsed, Vector2f position)
{

	spriteSheet.setSpritePosition(sf::Vector2f(position.x, position.y));
	spriteSheet.update(elapsed);
	
}

void SpriteGraphics::update(Game* game, float elapsed, Vector2f position)
{
	sprite.setPosition(sf::Vector2f(position.x, position.y));	
}
