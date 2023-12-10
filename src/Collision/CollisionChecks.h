#pragma once
#include "Circle.h"
#include "Rectangle.h"

namespace Collision
{
    bool checkIntersection(Circle circleOne, Circle circleTwo);
    bool checkIntersection(Rectangle rectangleOne, Rectangle rectangleTwo);
    bool checkIntersection(Rectangle rectangle, Circle circle);
}