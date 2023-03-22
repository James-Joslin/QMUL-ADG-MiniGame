#include "../../include/utils/Rectangle.h"
#include <vector>
#include <iostream>

bool Rectangle::inside(float x, float y) const
{
    if (x > this->getTopLeft().x and x < this->getBottomRight().x
        and y > this->getTopLeft().y and y < this->getBottomRight().y)
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

    std::vector<std::pair<float, float>> vertices{ {l1.x, l1.y}, {r1.x, l1.y}, {l1.x, r1.y}, {r1.x, r1.y} };
    // create a vector of vertices derived from l1 and r1 - teh vertices are coordinate pairs

    for (int i = 0; i < vertices.size(); i++)
    {
        std::pair<float, float> vertex = vertices[i];
        if (inside(vertex.first, vertex.second)) // cool inside function for each vertice
        {
            return true;
        }
    }
      
    // if none of the above are true then most be overlapping
    return false; // you can delete this once IX.B is complete.
}

