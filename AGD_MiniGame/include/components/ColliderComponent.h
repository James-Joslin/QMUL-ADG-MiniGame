#include "../../include/utils/Rectangle.h"
#include "../../include/graphics/Window.h"

class Entity;


class ColliderComponent : public Component
{
public:
	Rectangle& getBoundingBox() { return boundingBox; }
	Vector2f getBboxSize() { return bboxSize; }
	void setBboxSize(Vector2f _bboxSize) { bboxSize = _bboxSize; }
	void setBoundingBoxLocation(Vector2f position)
	{
		boundingBox.setTopLeft(position);
		boundingBox.setBottomRight(Vector2f((position.x + bboxSize.x), (position.y + bboxSize.y)));
	}
	void draw(Window* window) { window->draw(boundingBox.getDrawableRect()); }
	bool intersects(Rectangle& otherBbox)
	{
		return boundingBox.intersects(otherBbox);
	}
	void update(Vector2f position)
	{
		boundingBox.setTopLeft(position);
		boundingBox.setBottomRight(Vector2f((position.x + bboxSize.x), (position.y + bboxSize.y)));
	}

	ComponentID getID() { return ComponentID::COLLIDER; }

private:
	Rectangle boundingBox;
	Vector2f bboxSize;
};