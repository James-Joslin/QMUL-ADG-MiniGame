#include "../../include/utils/Rectangle.h"
#include <vector>
#include <iostream>

bool Rectangle::inside(float x, float y) const
{
    // <FEEDBACK> Better to check <= instead of < (resp. > and >=)
    // <Corrected> change operator 
    if (x >= this->getTopLeft().x and x <= this->getBottomRight().x
        and y >= this->getTopLeft().y and y <= this->getBottomRight().y)
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

    // coords for the rectangle rect
    Vector2f l1 = rect.getTopLeft();
    Vector2f r1 = rect.getBottomRight();

    // <FEEDBACK> Way too verbose. A rectangle is never going to have more than 4 vertices. Creating vectors, pair objects
    // <Corrected>
    //  and running a 'for' loop creates an unnecessary computational overhead.
    //  Simply make 4 calls (returning earlier if one is true) to inside (...). 

    if (inside(l1.x, l1.y) || inside(r1.x, l1.y) || inside(l1.x, r1.y) || inside (r1.x, r1.y))
    {
        return true;
    }
      
    // if none of the above are true then most be overlapping
    return false; // you can delete this once IX.B is complete.
}

