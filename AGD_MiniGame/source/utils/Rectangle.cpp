#include "../../include/utils/Rectangle.h"


bool Rectangle::inside(float x, float y) const
{
    // IX.A Implement this function, that returns true if the point <x,y> is inside this rectangle.
    if (
        x > this->getTopLeft().x and x < this->getBottomRight().x 
        and 
        y > this->getBottomRight().y and y < this->getTopLeft().y
    )
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Rectangle::intersects(const Rectangle& rect) const
{
    // IX.B Implement this function, that returns true if the rectangle "rect" overlaps with this rectangle.
    // coords for this rectangle
    Vector2f l1 = this->getTopLeft();
    Vector2f r1 = this->getBottomRight();

    // coords for other rectangle
    Vector2f l2 = rect.getTopLeft();
    Vector2f r2 = rect.getBottomRight();

    // check if either entities have area of zero (sanity check) - add error handling as well?
    if (l1.x == r1.x || l1.y == r1.y || l2.x == r2.x || l2.y == r2.y)
    {
        return false;
    }
    // If one rectangle is on left side of other - then not overlapping
    if (l1.x > r2.x || l2.x > r1.x)
    {
        return false;
    }
    // If one rectangle is above the other - then not overlapping
    if (r1.y > l2.y || r2.y > l1.y)
    {
        return false;
    }
    // if none of the above are true then most be overlapping
    return true; // you can delete this once IX.B is complete.
}

