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

void SpriteGraphics::draw(Window* window)
{
	if (isSpriteSheet)
	{
		throw std::exception("You are trying to draw an animated sprite sheet as if it were a still sprite");
	}
	else
	{
		window->draw(sprite);
	}
}

void SpriteSheetGraphics::draw(Window* window)
{
	if (isSpriteSheet)
	{
		sf::Sprite* sp = &spriteSheet.getSprite();
		const sf::Vector2f pos = sp->getPosition();
		window->draw(spriteSheet.getSprite());
	}
	else
	{
		throw std::exception("This is a spritesheet");
	}
}

void SpriteGraphics::setPosition(std::unique_ptr<PositionComponent> _positionComponent, float x, float y)
{
	_positionComponent->setPosition(x, y);
	if (isSpriteSheet)
	{
		throw std::exception("Sprite sheet being used when setting position with sprite graphcs component");
	}
	else
	{
		sprite.setPosition(
			_positionComponent->getPosition().x,
			_positionComponent->getPosition().y
		);
	}
}

void SpriteSheetGraphics::setPosition(std::unique_ptr<PositionComponent> _positionComponent, float x, float y)
{
	_positionComponent->setPosition(x, y);
	if (isSpriteSheet)
	{
		spriteSheet.getSprite().setPosition(
			_positionComponent->getPosition().x,
			_positionComponent->getPosition().y
		);
	}
	else
	{
		throw std::exception("Sprite being used when setting position with object with animated sprite sheet");
	}
}

void SpriteSheetGraphics::setAnimation(const std::string &name, bool play, bool loop)
{
	spriteSheet.setAnimation(name, play, loop);
}

void SpriteSheetGraphics::setSpriteDirection(Direction direction)
{
	spriteSheet.setSpriteDirection(direction);
}