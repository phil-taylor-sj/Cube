#pragma once
#include "Physics/Circle.h"
#include "Physics/Rectangle.h"
#include <cmath>
#include <memory>
#include <array>
#include <algorithm>

namespace Physics
{   
    /**
     * @struct RectCorners
     * @brief A structure representing the corner positions of a rectangle.
     */
    struct RectCorners {
        float leftUpperXY[2] = {0.f, 0.f};
        float leftLowerXY[2] = {0.f, 0.f};
        float rightUpperXY[2] = {0.f, 0.f};
        float rightLowerXY[2] = {0.f, 0.f};
    };

    const double pi = 3.141592653589793; ///< The parameters of the Rectangle.

    /**
     * @brief Check if two circles intersect.
     * @param circleOne The parameters of the first circle.
     * @param circleTwo The parameters of the second circle.
     * @return True if the circles intersect, false otherwise.
     *
     * This function checks if two circles intersect by comparing the distance
     * between their centers with the sum of their radii.
     */
    bool checkIntersection(const CircleParams& circleOne, const CircleParams& circleTwo);

    /**
     * @brief Check if a circle intersects with a rectangle.
     * @param rectangleIn The parameters of the rectangle.
     * @param circleIn The parameters of the circle.
     * @return True if the circle intersects with the rectangle, false otherwise.
     *
     * This function checks if a circle intersects with a rectangle by considering
     * various conditions, including the positions of the circle's center relative
     * to the rectangle and its boundaries.
     */
    bool checkIntersection(Vec2f pointPosition, const RectParams& rectangleIn);

    /**
     * @brief Check if a circle intersects with a rectangle.
     * @param rectangleIn The parameters of the rectangle.
     * @param circleIn The parameters of the circle.
     * @return True if the circle intersects with the rectangle, false otherwise.
     *
     * This function checks if a circle intersects with a rectangle by considering
     * various conditions, including the positions of the circle's center relative
     * to the rectangle and its boundaries.
     */
    bool checkIntersection(const RectParams& rectangleIn, const CircleParams& circleIn);

    /**
     * @brief Check if two rectangles intersect.
     * @param rectangleOneIn The parameters of the first rectangle.
     * @param rectangleTwoIn The parameters of the second rectangle.
     * @return True if the rectangles intersect, false otherwise.
     *
     * This function checks if two rectangles intersect by considering their positions
     * and dimensions. If either rectangle is rotated, a more complex check is performed.
     */
    bool checkIntersection(const RectParams& rectangleOneIn, const RectParams& rectangleTwoIn);

    /**
     * @brief Calculate the corner positions of a rotated rectangle.
     * @param rectCompare The parameters of the rectangle.
     * @return The corner positions as a RectCorners structure.
     *
     * This function calculates the corner positions of a rotated rectangle by
     * considering its angle of rotation and dimensions. The corners are returned
     * as a RectCorners structure.
     */
    RectCorners calculateCornerPositions(RectParams params);
    
    /**
     * @brief Compare two unaligned rectangles for intersection.
     * @param rectBase The parameters of the base rectangle.
     * @param rectCompare The corner positions of the comparison rectangle.
     * @return True if the rectangles intersect, false otherwise.
     *
     * This function compares two unaligned rectangles for intersection by taking into
     * account the positions of their corners and the rotation of the base rectangle.
     */
    bool compareUnalignedRectangles(RectParams paramsBase, RectCorners params);

    /**
     * @brief Apply a rotation matrix to a point.
     * @param point The input point as an array of size 2.
     * @param matrix The rotation matrix as a 2x2 array.
     * @return The rotated point as an array of size 2.
     *
     * This function applies a 2D rotation matrix to a point, resulting in a new
     * rotated point. The rotation matrix is specified as a 2x2 array.
     */
    std::array<float, 2> applyRotationMatrix(std::array<float, 2> point, float matrix[2][2]);
}