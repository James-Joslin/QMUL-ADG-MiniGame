#include "../../include/utils/Rectangle.h"
#include "../../include/graphics/Window.h"

class Entity;


class ColliderComponent
{
public:

	//<FEEDBACK> The move verbose methods below should be in the CPP	
	//<CORRECTED> made a new cpp file and placed more verbose functions in it

	Rectangle& getBoundingBox() { return boundingBox; }
	Vector2f getBboxSize() { return bboxSize; }
	void setBboxSize(Vector2f _bboxSize) { bboxSize = _bboxSize; }
	void setBoundingBoxLocation(Vector2f position);
	void draw(Window* window) { window->draw(boundingBox.getDrawableRect()); }
	bool intersects(Rectangle& otherBbox) { return boundingBox.intersects(otherBbox); }
	void update(Vector2f position);

private:
	Rectangle boundingBox;
	Vector2f bboxSize;
};