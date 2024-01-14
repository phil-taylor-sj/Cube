#pragma once
#include "Physics/Circle.h"
#include "Physics/Rectangle.h"
#include <cmath>
#include <memory>
#include <array>
#include <algorithm>

namespace Physics
{   
    struct RectCorners {
        float leftUpperXY[2] = {0.f, 0.f};
        float leftLowerXY[2] = {0.f, 0.f};
        float rightUpperXY[2] = {0.f, 0.f};
        float rightLowerXY[2] = {0.f, 0.f};
    };
    const double pi = 3.141592653589793;
    bool checkIntersection(const CircleParams& circleOne, const CircleParams& circleTwo);
    bool checkIntersection(const RectParams& rectangleIn, const CircleParams& circleIn);
    bool checkIntersection(const RectParams& rectangleOneIn, const RectParams& rectangleTwoIn);


    RectCorners calculateCornerPositions(RectParams params);
    bool compareUnalignedRectangles(RectParams paramsBase, RectCorners params);
    std::array<float, 2> applyRotationMatrix(std::array<float, 2> point, float matrix[2][2]);
}