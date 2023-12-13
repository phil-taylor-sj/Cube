#pragma once
#include "Collision/Circle.h"
#include "Collision/Rectangle.h"
#include <cmath>
#include <memory>
#include <array>
#include <algorithm>

namespace Collision
{   
    struct RectCorners {
        float leftUpperXY[2] = {0.f, 0.f};
        float leftLowerXY[2] = {0.f, 0.f};
        float rightUpperXY[2] = {0.f, 0.f};
        float rightLowerXY[2] = {0.f, 0.f};
    };
    const double pi = 3.141592653589793;
    bool checkIntersection(Circle circleOne, Circle circleTwo);
    bool checkIntersection(Rectangle rectangleOne, Rectangle rectangleTwo);
    bool checkIntersection(Rectangle rectangle, Circle circle);

    RectCorners calculateCornerPositions(RectParams params);
    bool compareUnalignedRectangles(RectParams paramsBase, RectCorners params);
    std::array<float, 2> applyRotationMatrix(std::array<float, 2> point, float matrix[2][2]);
}