#include "../graphics/SpriteSheet.h"
#include "../../include/components/PositionComponent.h"
#include "SFML/Graphics.hpp"
#include <iostream>
#include <memory>

class Window;
class Game;

#pragma once
// Graphics interface with virutal components
class GraphicsComponent
{
public:

	//<FEEDBACK> Several of these functions (especially, the getters) should be const
	//<CORRECTED> Added const to the getters of the base and inherited classes

	~GraphicsComponent() {};
	virtual void init(const std::string& textureFile, float scale) = 0;
	virtual void initSpriteSheet(const std::string& spriteSheetFile) = 0;
	virtual sf::Vector2i getTextureSize() const = 0;
	virtual sf::Vector2i getSpriteSize() const = 0;
	virtual sf::Vector2f getScale() const = 0; // gets texture scale
	virtual sf::Vector2f getSpriteScale() const = 0; // gets sprite scale (out of sprite sheet)
	virtual void draw(Window* window) = 0;
	virtual void setPosition(Vector2f position) = 0;
	virtual void setAnimation(const std::string& name, bool play, bool loop) = 0;
	virtual Direction getSpriteDirection() const  = 0;
	virtual void setSpriteDirection(Direction direction) = 0;
	virtual SpriteSheet* getSpriteSheet() = 0;
	virtual sf::Sprite getSprite() const = 0;
	virtual void update(Game* game, float elapsed, Vector2f) = 0;
};

// Subclasses - Sprite Graphics
class SpriteGraphics : public GraphicsComponent
{
public:
	void init(const std::string& textureFile, float scale) override; // in Graphics Components cpp
	void initSpriteSheet(const std::string& spriteSheetFile) override; // in Graphics Components cpp // will return an exception
	sf::Vector2i getTextureSize() const override { return sf::Vector2i(static_cast<int>(texture.getSize().x), static_cast<int>(texture.getSize().y)); }
	sf::Vector2i getSpriteSize() const override
	{
		throw std::exception(
			"You are calling a function that would get a sprite's size from a sprite sheet, however this is a singular sprite and therefore doesn't have a sprite sheet\nYou should be calling getTextureSize()");
	}
	sf::Vector2f getScale() const override { return sprite.getScale(); }
	sf::Vector2f getSpriteScale() const override
	{
		throw std::exception(
			"You are calling a function that would get a sprite's scale from a sprite sheet, however this is a singular sprite and therefore doesn't have a sprite sheet\nYou should be calling getScale()");
	}
	virtual void draw(Window* window) override; // in Graphics Components cpp
	virtual void setPosition(Vector2f position) override;
	void setAnimation(const std::string& name, bool play, bool loop) override {}
	void setSpriteDirection(Direction direction) override {}
	sf::Sprite getSprite() const override { return sprite; }
	SpriteSheet* getSpriteSheet() { throw std::exception("No spritesheet available"); }
	Direction getSpriteDirection() const { throw std::exception("No spritesheet available"); }
	virtual void update(Game* game, float elapsed, Vector2f) override;

private:
	sf::Texture texture;
	sf::Sprite sprite;

	//<FEEDBACK> You don't need this variable
	//<CORRECTED> Variable isSpriteSheet removed
	//bool isSpriteSheet{ false };
};

// Subclasses - Sprite Sheet Graphics
class SpriteSheetGraphics : public GraphicsComponent
{
public:
	void init(const std::string& textureFile, float scale) override; // in Graphics Components cpp // will return an exception
	void initSpriteSheet(const std::string& spriteSheetFile) override; // in Graphics Components cpp
	sf::Vector2i getTextureSize() const override { return spriteSheet.getSpriteSize(); }
	sf::Vector2i getSpriteSize() const override { return spriteSheet.getSpriteSize(); }
	sf::Vector2f getScale() const override
	{
		throw std::exception(
			"You are calling a function that would get the scale from a sprite, however this is a sprite sheet and therefore you must first address the sheet to get the sprite and its scale\nYou should be calling getSpriteScale()");
	}
	sf::Vector2f getSpriteScale() const override { return spriteSheet.getSpriteScale(); }
	virtual void draw(Window* window) override; // in Graphics Components cpp
	void setPosition(Vector2f position) override;
	void setAnimation(const std::string& name, bool play, bool loop) override;
	void setSpriteDirection(Direction direction) override;
	Direction getSpriteDirection() const { return spriteSheet.getSpriteDirection(); }
	sf::Sprite getSprite() const override { throw std::exception("No sprite available"); }
	SpriteSheet* getSpriteSheet() { return &spriteSheet; }
	virtual void update(Game* game, float elapsed, Vector2f) override;

private:
	SpriteSheet spriteSheet;

	//<FEEDBACK> You don't need this variable
	//<CORRECTED> Variable isSpriteSheet removed
	//bool isSpriteSheet{ true };
};