#include "CollisionChecks.h"


namespace Collision
{
    bool checkIntersection(Circle circleOne, Circle circleTwo)
    {
        CircleParams paramsOne = circleOne.getCircle();
        CircleParams paramsTwo = circleTwo.getCircle();
        float centreSpacing = sqrt(
            pow(abs(paramsOne.x - paramsTwo.x),2) +
            pow(abs(paramsOne.y - paramsTwo.y),2)
        );
        float totalRadius = paramsOne.radius + paramsTwo.radius;
        return centreSpacing <= totalRadius;
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
            return false;

        }
    }

    bool checkIntersection(Rectangle rectangle, Circle circle)
    {
        return false;
    }
}