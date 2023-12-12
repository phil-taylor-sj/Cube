#pragma once
#include "Circle.h"
#include "Rectangle.h"
#include <cmath>
#include <memory>
#include <array>
#include <algorithm>

namespace Collision
{
    bool checkIntersection(Circle circleOne, Circle circleTwo);
    bool checkIntersection(Rectangle rectangleOne, Rectangle rectangleTwo);
    bool checkIntersection(Rectangle rectangle, Circle circle);
    struct RectCorners;
    RectCorners calculateCornerPositions(RectParams params);
    bool compareUnalignedRectangles(RectParams paramsBase, RectCorners params);
    std::array<float, 2> applyRotationMatrix(std::array<float, 2> point, float matrix[2][2]);
}