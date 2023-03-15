#include "../graphics/SpriteSheet.h"
#include "../../include/utils/Vector2.h"
#include "../../include/graphics/Window.h"
#include "SFML/Graphics.hpp"
#include <iostream>
#include <memory>

#pragma once
// Graphics interface with virutal components
class GraphicsComponent
{
public:
	~GraphicsComponent() {};
	virtual void init(const std::string& textureFile, float scale) = 0;
	virtual void initSpriteSheet(const std::string& spriteSheetFile) = 0;
	virtual sf::Vector2u getTextureSize() = 0;
	virtual sf::Vector2i getSpriteSize() = 0;
	virtual sf::Vector2f getScale() = 0; // gets texture scale
	virtual sf::Vector2f getSpriteScale() = 0; // gets sprite scale (out of sprite sheet)
	//virtual void update() = 0;
	virtual void draw(Window* window) = 0;
};

// Subclasses - Sprite Graphics
class SpriteGraphics : public GraphicsComponent
{
public:
	void init(const std::string& textureFile, float scale) override;
	void initSpriteSheet(const std::string& spriteSheetFile) override; // will return an exception
	sf::Vector2u getTextureSize() override { return texture.getSize(); }
	sf::Vector2i getSpriteSize() override {}
	sf::Vector2f getScale() override { return sprite.getScale(); }
	sf::Vector2f getSpriteScale() override {}
	virtual void draw(Window* window) override;

private:
	sf::Texture texture;
	sf::Sprite sprite;
	bool isSpriteSheet{ false };
};

// Subclasses - Sprite Sheet Graphics
class SpriteSheetGraphics : public GraphicsComponent
{
public:
	void init(const std::string& textureFile, float scale) override; // will return an exception
	void initSpriteSheet(const std::string& spriteSheetFile) override;
	sf::Vector2u getTextureSize() override {};
	sf::Vector2i getSpriteSize() override { return spriteSheet.getSpriteSize(); }
	sf::Vector2f getScale() override {}
	sf::Vector2f getSpriteScale() override { return spriteSheet.getSpriteScale(); }
	virtual void draw(Window* window) override;

private:
	SpriteSheet spriteSheet;
	bool isSpriteSheet{ true };
};