#include "../../include/components/ColliderComponent.h"

void ColliderComponent::update(bool _isSpriteSheet, Vector2f position)
{
	// <FEEDABCK> I don't understand why do you need isSpriteSheet, it shouldn't matter.

	if (_isSpriteSheet) // bounding box stuff handled by collision component?
	{
		boundingBox.setTopLeft(position);
		boundingBox.setBottomRight(Vector2f((position.x + bboxSize.x), (position.y + bboxSize.y)));
	}
}