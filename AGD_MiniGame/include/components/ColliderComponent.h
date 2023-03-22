#include "../../include/utils/Rectangle.h"
#include "../../include/graphics/Window.h"

class ColliderComponent
{
public:

	// <FEEDBACK> The more verbose methods below should be in the CPP.

	Rectangle& getBoundingBox() { return boundingBox; }
	Vector2f getBboxSize() { return bboxSize; }
	void setBboxSize(Vector2f _bboxSize) { bboxSize = _bboxSize; }
	void setBoundingBoxSize(Vector2f _bboxSize) { bboxSize = Vector2f(_bboxSize.x, _bboxSize.y); }
	void setBoundingBoxLocation(Vector2f position)
	{
		boundingBox.setTopLeft(position);
		boundingBox.setBottomRight(Vector2f((position.x + bboxSize.x), (position.y + bboxSize.y)));
	}
	void draw(Window* window) 
	{ 

		window->draw(boundingBox.getDrawableRect()); 
	}
	void update(bool _isSpriteSheet, Vector2f position);

private:
	Rectangle boundingBox;
	Vector2f bboxSize;
};