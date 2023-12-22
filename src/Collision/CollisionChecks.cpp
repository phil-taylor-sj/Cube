#include "Collision/CollisionChecks.h"

namespace Collision
{

    bool checkIntersection(Circle circleOne, Circle circleTwo)
    {
        CircleParams paramsOne = circleOne.getCircle();
        CircleParams paramsTwo = circleTwo.getCircle();
        float centreSpacing = sqrt(
            pow(abs(paramsOne.x - paramsTwo.x), 2) +
            pow(abs(paramsOne.y - paramsTwo.y), 2)
        );
        float totalRadius = paramsOne.radius + paramsTwo.radius;
        return centreSpacing <= totalRadius;
    }

    bool checkIntersection(Rectangle rectangle, Circle circle)
    {
        RectParams paramsRect = rectangle.getRectangle();
        CircleParams paramsCircle = circle.getCircle();

        if (paramsRect.angle > 0.f)
        {
            paramsCircle.x = paramsCircle.x - paramsRect.x;
            paramsCircle.y = paramsCircle.y - paramsRect.y;

            float cosAngle = cos(-1.f * paramsRect.angle * pi / 180.);
            float sinAngle = sin(-1.f * paramsRect.angle * pi / 180.);
            float newX = paramsCircle.x * cosAngle - paramsCircle.y * sinAngle;
            float newY = paramsCircle.x * sinAngle + paramsCircle.y * cosAngle;

            paramsCircle.x = newX;
            paramsCircle.y = newY;
            paramsRect.x = 0.f;
            paramsRect.y = 0.f;
        }

        float rectX = paramsRect.x;
        float rectY = paramsRect.y;
        float halfWidth = paramsRect.halfWidth;
        float halfHeight = paramsRect.halfHeight;

        float leftBoundary = rectX - (halfWidth + paramsCircle.radius);
        float rightBoundary = rectX + (halfWidth + paramsCircle.radius);
        float upperBoundary = rectY - (halfHeight + paramsCircle.radius);
        float lowerBoundary = rectY + (halfHeight + paramsCircle.radius);

        if (paramsCircle.x <= leftBoundary ||
            paramsCircle.x >= rightBoundary ||
            paramsCircle.y <= upperBoundary ||
            paramsCircle.y >= lowerBoundary
            )
        {
            return false;
        }

        // Calculate location of rectangle corners.
        float leftUpper[2] = { rectX - halfWidth, rectY - halfHeight };
        float leftLower[2] = { rectX - halfWidth, rectY + halfHeight };
        float rightUpper[2] = { rectX + halfWidth, rectY - halfHeight };
        float rightLower[2] = { rectX + halfWidth, rectY + halfHeight };

        // Check circle position against upper left corner.
        float leftUpperDistance = sqrt(
            pow(paramsCircle.x - leftUpper[0], 2) +
            pow(paramsCircle.y - leftUpper[1], 2)
        );
        if (paramsCircle.x < leftUpper[0] &&
            paramsCircle.y < leftUpper[1] &&
            leftUpperDistance >= paramsCircle.radius)
        {
            return false;

        }

        // Check circle position against lower left corner.
        float leftLowerDistance = sqrt(
            pow(paramsCircle.x - leftLower[0], 2) +
            pow(paramsCircle.y - leftLower[1], 2)
        );
        if (paramsCircle.x < leftLower[0] &&
            paramsCircle.y > leftLower[1] &&
            leftLowerDistance >= paramsCircle.radius)
        {
            return false;

        }


        // Check circle position against upper right corner.
        float rightUpperDistance = sqrt(
            pow(paramsCircle.x - rightUpper[0], 2) +
            pow(paramsCircle.y - rightUpper[1], 2)
        );
        if (paramsCircle.x > rightUpper[0] &&
            paramsCircle.y < rightUpper[1] &&
            rightUpperDistance >= paramsCircle.radius)
        {
            return false;

        }

        // Check circle position against lower right corner.
        float rightLowerDistance = sqrt(
            pow(paramsCircle.x - rightLower[0], 2) +
            pow(paramsCircle.y - rightLower[1], 2)
        );
        if (paramsCircle.x > rightLower[0] &&
            paramsCircle.y > rightLower[1] &&
            rightLowerDistance >= paramsCircle.radius)
        {
            return false;

        }

        return true;
    }

    bool checkIntersection(Rectangle rectangleOne, Rectangle rectangleTwo)
    {
        RectParams paramsOne = rectangleOne.getRectangle();
        RectParams paramsTwo = rectangleTwo.getRectangle();

        if (paramsOne.angle == 0. && paramsTwo.angle == 0.)
        {
            float leftSideOne = paramsOne.x - paramsOne.halfWidth;
            float leftSideTwo = paramsTwo.x - paramsTwo.halfWidth;

            float rightSideOne = paramsOne.x + paramsOne.halfWidth;
            float rightSideTwo = paramsTwo.x + paramsTwo.halfWidth;

            float upperSideOne = paramsOne.y - paramsOne.halfHeight;
            float upperSideTwo = paramsTwo.y - paramsTwo.halfHeight;

            float lowerSideOne = paramsOne.y + paramsOne.halfHeight;
            float lowerSideTwo = paramsTwo.y + paramsTwo.halfHeight;

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
            RectCorners cornersOne = calculateCornerPositions(paramsOne);
            RectCorners cornersTwo = calculateCornerPositions(paramsTwo);

            return !(compareUnalignedRectangles(paramsOne, cornersTwo) ||
                compareUnalignedRectangles(paramsTwo, cornersOne));
        }
    }

    RectCorners calculateCornerPositions(RectComponent rectCompare)
    {
        float cosAngle = cos(rectCompare.angle * pi / 180.);
        float sinAngle = sin(rectCompare.angle * pi / 180.);

        float cosX = rectCompare.halfWidth * cosAngle;
        float sinX = rectCompare.halfWidth * sinAngle;
        float cosY = rectCompare.halfHeight * cosAngle;
        float sinY = rectCompare.halfHeight * sinAngle;

        RectCorners corners = RectCorners();
        corners.leftUpperXY[0] = (-1.f * cosX) - (-1.f * sinY) + rectCompare.x,
        corners.leftUpperXY[1] = (-1.f * sinX) + (-1.f * cosY) + rectCompare.y;
        
        corners.leftLowerXY[0] = (-1.f * cosX) - sinY + rectCompare.x,
        corners.leftLowerXY[1] = (-1.f * sinX) + cosY + rectCompare.y;
        
        corners.rightUpperXY[0] = cosX - (-1.f * sinY) + rectCompare.x,
        corners.rightUpperXY[1] = sinX + (-1.f * cosY) + rectCompare.y;

        corners.rightLowerXY[0] = cosX - sinY + rectCompare.x;
        corners.rightLowerXY[1] = sinX + cosY + rectCompare.y;

        return corners;
    }

    bool compareUnalignedRectangles(RectComponent rectBase, RectCorners rectCompare)
    {
        float rotationMatrix[2][2] = {
            {cos(-1.f * rectBase.angle * pi / 180.),
            -1.f * sin(-1.f * rectBase.angle * pi / 180.)},
            {sin(-1.f * rectBase.angle * pi / 180.),
            cos(-1.f * rectBase.angle * pi / 180.)}
        };

        std::array<float, 2> leftUpperXY = applyRotationMatrix(
            std::array<float, 2> {
                rectCompare.leftUpperXY[0] - rectBase.x,
                rectCompare.leftUpperXY[1] - rectBase.y
            },
            rotationMatrix
        );

        std::array<float, 2> leftLowerXY = applyRotationMatrix(
            std::array<float, 2> {
                rectCompare.leftLowerXY[0] - rectBase.x,
                rectCompare.leftLowerXY[1] - rectBase.y
            },
            rotationMatrix
        );

        std::array<float, 2> rightUpperXY = applyRotationMatrix(
            std::array<float, 2> {
                rectCompare.rightUpperXY[0] - rectBase.x,
                rectCompare.rightUpperXY[1] - rectBase.y
            },
            rotationMatrix
        );

        std::array<float, 2> rightLowerXY = applyRotationMatrix(
            std::array<float, 2> {
                rectCompare.rightLowerXY[0] - rectBase.x,
                rectCompare.rightLowerXY[1] - rectBase.y
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