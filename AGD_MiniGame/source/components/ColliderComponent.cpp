#include "../../include/components/ColliderComponent.h"

void ColliderComponent::update(bool _isSpriteSheet, Vector2f position)
{
	if (_isSpriteSheet) // bounding box stuff handled by collision component?
	{
		boundingBox.setTopLeft(position);
		boundingBox.setBottomRight(Vector2f((position.x + bboxSize.x), (position.y + bboxSize.y)));
	}
}