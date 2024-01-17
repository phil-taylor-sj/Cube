#include "Physics/CollisionChecks.h"

namespace Physics
{

    bool checkIntersection(const CircleParams& circleOne, const CircleParams& circleTwo)
    {
        float centreSpacing = circleOne.position.distance(
            circleTwo.position
        );
         
        float totalRadius = circleOne.radius + circleTwo.radius;
        return centreSpacing <= totalRadius;
    }

    bool checkIntersection(const RectParams& rectangleIn, const CircleParams& circleIn)
    {
        RectParams rectangle = rectangleIn;
        CircleParams circle = circleIn;

        if (rectangle.angle > 0.f)
        {
            circle.position = circle.position - rectangle.position;

            circle.position.applyRotation(-1.f * rectangle.angle);
            
            rectangle.position.x = 0.f;
            rectangle.position.y = 0.f;
        }

        float leftBound = rectangle.position.x - (rectangle.halfWidth + circle.radius);
        float rightBound = rectangle.position.x + (rectangle.halfWidth + circle.radius);
        float upperBound = rectangle.position.y - (rectangle.halfHeight + circle.radius);
        float lowerBound = rectangle.position.y + (rectangle.halfHeight + circle.radius);

        if (circle.position.x <= leftBound ||
            circle.position.x >= rightBound ||
            circle.position.y <= upperBound ||
            circle.position.y >= lowerBound
            )
        {
            return false;
        }

        // Calculate location of rectangle corners.
        Vec2f leftUpper = rectangle.position  + 
            Vec2f(-1.f* rectangle.halfWidth, -1.f * rectangle.halfHeight);
        
        Vec2f leftLower = rectangle.position  + 
            Vec2f(-1.f* rectangle.halfWidth, rectangle.halfHeight);
        
        Vec2f rightUpper = rectangle.position + 
            Vec2f(rectangle.halfWidth, -1.f * rectangle.halfHeight);
        
        Vec2f rightLower = rectangle.position + 
            Vec2f(rectangle.halfWidth, rectangle.halfHeight);

        // Check circle position against upper left corner.
        float leftUpperDistance = circle.position.distance(leftUpper);
        if (circle.position.x < leftUpper.x &&
            circle.position.y < leftUpper.y &&
            leftUpperDistance >= circle.radius)
        {
            return false;

        }

        // Check circle position against lower left corner.
        float leftLowerDistance = circle.position.distance(leftLower);
        if (circle.position.x < leftLower.x &&
            circle.position.y > leftLower.y &&
            leftLowerDistance >= circle.radius)
        {
            return false;

        }


        // Check circle position against upper right corner.
        float rightUpperDistance = circle.position.distance(rightUpper);
        if (circle.position.x > rightUpper.x &&
            circle.position.y < rightUpper.y &&
            rightUpperDistance >= circle.radius)
        {
            return false;

        }

        // Check circle position against lower right corner.
        float rightLowerDistance = circle.position.distance(rightLower);
        if (circle.position.x > rightLower.x &&
            circle.position.y > rightLower.y &&
            rightLowerDistance >= circle.radius)
        {
            return false;
        }

        return true;
    }

    bool checkIntersection(const RectParams& rectangleOneIn, 
        const RectParams& rectangleTwoIn)
    {
        RectParams rectOne = rectangleOneIn;
        RectParams rectTwo = rectangleTwoIn;

        if (rectOne.angle == 0. && rectTwo.angle == 0.)
        {
            float leftSideOne = rectOne.position.x - rectOne.halfWidth;
            float leftSideTwo = rectTwo.position.x - rectTwo.halfWidth;

            float rightSideOne = rectOne.position.x + rectOne.halfWidth;
            float rightSideTwo = rectTwo.position.x + rectTwo.halfWidth;

            float upperSideOne = rectOne.position.y - rectOne.halfHeight;
            float upperSideTwo = rectTwo.position.y - rectTwo.halfHeight;

            float lowerSideOne = rectOne.position.y + rectOne.halfHeight;
            float lowerSideTwo = rectTwo.position.y + rectTwo.halfHeight;

            if (rightSideOne <= leftSideTwo || rightSideTwo <= leftSideOne)
            {
                return false;
            }
            if (lowerSideOne <= upperSideTwo || lowerSideTwo <= upperSideOne)
            {
                return false;
            }
            return true;
        }
        else
        {
            RectCorners cornersOne = calculateCornerPositions(rectOne);
            RectCorners cornersTwo = calculateCornerPositions(rectTwo);

            return !(compareUnalignedRectangles(rectOne, cornersTwo) ||
                compareUnalignedRectangles(rectTwo, cornersOne));
        }
    }

    RectCorners calculateCornerPositions(RectParams rectCompare)
    {
        float cosAngle = cos(rectCompare.angle * pi / 180.);
        float sinAngle = sin(rectCompare.angle * pi / 180.);

        float cosX = rectCompare.halfWidth * cosAngle;
        float sinX = rectCompare.halfWidth * sinAngle;
        float cosY = rectCompare.halfHeight * cosAngle;
        float sinY = rectCompare.halfHeight * sinAngle;

        RectCorners corners = RectCorners();
        corners.leftUpperXY[0] = (-1.f * cosX) - (-1.f * sinY) + rectCompare.position.x,
        corners.leftUpperXY[1] = (-1.f * sinX) + (-1.f * cosY) + rectCompare.position.y;
        
        corners.leftLowerXY[0] = (-1.f * cosX) - sinY + rectCompare.position.x,
        corners.leftLowerXY[1] = (-1.f * sinX) + cosY + rectCompare.position.y;
        
        corners.rightUpperXY[0] = cosX - (-1.f * sinY) + rectCompare.position.x,
        corners.rightUpperXY[1] = sinX + (-1.f * cosY) + rectCompare.position.y;

        corners.rightLowerXY[0] = cosX - sinY + rectCompare.position.x;
        corners.rightLowerXY[1] = sinX + cosY + rectCompare.position.y;

        return corners;
    }

    bool compareUnalignedRectangles(RectParams rectBase, RectCorners rectCompare)
    {
        float rotationMatrix[2][2] = {
            {cos(-1.f * rectBase.angle * pi / 180.),
            -1.f * sin(-1.f * rectBase.angle * pi / 180.)},
            {sin(-1.f * rectBase.angle * pi / 180.),
            cos(-1.f * rectBase.angle * pi / 180.)}
        };

        std::array<float, 2> leftUpperXY = applyRotationMatrix(
            std::array<float, 2> {
                rectCompare.leftUpperXY[0] - rectBase.position.x,
                rectCompare.leftUpperXY[1] - rectBase.position.y
            },
            rotationMatrix
        );

        std::array<float, 2> leftLowerXY = applyRotationMatrix(
            std::array<float, 2> {
                rectCompare.leftLowerXY[0] - rectBase.position.x,
                rectCompare.leftLowerXY[1] - rectBase.position.y
            },
            rotationMatrix
        );

        std::array<float, 2> rightUpperXY = applyRotationMatrix(
            std::array<float, 2> {
                rectCompare.rightUpperXY[0] - rectBase.position.x,
                rectCompare.rightUpperXY[1] - rectBase.position.y
            },
            rotationMatrix
        );

        std::array<float, 2> rightLowerXY = applyRotationMatrix(
            std::array<float, 2> {
                rectCompare.rightLowerXY[0] - rectBase.position.x,
                rectCompare.rightLowerXY[1] - rectBase.position.y
            },
            rotationMatrix
        );

        std::array<float, 4> cornersX = {
            leftUpperXY[0], leftLowerXY[0],
            rightUpperXY[0], rightLowerXY[0]
        };

        std::array<float, 4> cornersY = {
            leftUpperXY[1], leftLowerXY[1],
            rightUpperXY[1], rightLowerXY[1]
        };

        float minX = *std::min_element(cornersX.begin(), cornersX.end());
        float maxX = *std::max_element(cornersX.begin(), cornersX.end());
        float minY = *std::min_element(cornersY.begin(), cornersY.end());
        float maxY = *std::max_element(cornersY.begin(), cornersY.end());

        return ( minX >= rectBase.halfWidth ||
                 maxX <= -1.f * rectBase.halfWidth ||
                 minY >= rectBase.halfHeight ||
                 maxY <= -1.f * rectBase.halfHeight
            );
    }


    std::array<float, 2> applyRotationMatrix(std::array<float, 2> point, float matrix[2][2])
    {
        std::array<float, 2> rotatedPoint {
            point[0] * matrix[0][0] + point[1] * matrix[0][1],
            point[0] * matrix[1][0] + point[1] * matrix[1][1]
        };
        return rotatedPoint;
    }
}