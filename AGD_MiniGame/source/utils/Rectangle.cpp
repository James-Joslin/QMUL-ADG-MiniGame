#include "../../include/utils/Rectangle.h"
#include <vector>
#include <iostream>

bool Rectangle::inside(float x, float y) const
{
    // IX.A Implement this function, that returns true if the point <x,y> is inside this rectangle.
    if (
        x > this->getTopLeft().x and x < this->getBottomRight().x 
        and 
        y > this->getBottomRight().y and y < this->getTopLeft().y
    )
    {
        std::cout << "Yup" << std::endl;
        return true;
    }
    else
    {
        std::cout << "Nope" << std::endl;
        return false;
    }
}

bool Rectangle::intersects(const Rectangle& rect) const
{
    // IX.B Implement this function, that returns true if the rectangle "rect" overlaps with this rectangle.
    // coords for this rectangle

    // coords for other rectangle
    Vector2f l1 = rect.getTopLeft();
    Vector2f r1 = rect.getBottomRight();

    std::vector<std::pair<float, float>> vertices{ {l1.x, l1.y}, {r1.x, l1.y}, {l1.x, r1.y}, {r1.x, r1.y} };

    for (int i = 0; i < vertices.size(); i++)
    {
        std::pair<float, float> vertex = vertices[i];
        if (this->inside(vertex.first, vertex.second))
        {
            return true;
        }
    }
      
    // if none of the above are true then most be overlapping
    return false; // you can delete this once IX.B is complete.
}

