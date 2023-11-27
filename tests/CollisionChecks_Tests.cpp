#include "pch.h"
//#include "../src/Collision/Circle.cpp"
#include "../src/Collision/CollisionChecks.cpp"

namespace Coll = Collision;

namespace CollisionChecks_Tests
{
    TEST(CollisionChecks_Intersects_Test,
        Two_circle_arguments_which_do_not_intersect_should_return_false)
    {
        Coll::Circle circleBase = Coll::Circle(225.5, 300.0, 100.0);
        Coll::Circle circleOne = Coll::Circle(425.0, 397.2, 100.0);
        Coll::Circle circleTwo = Coll::Circle(420.0, 350.0, 100.0);
        Coll::Circle circleThree = Coll::Circle(370.0, 360.0, 50.0);
 
        ASSERT_FALSE(Coll::checkIntersection(circleBase, circleOne));
        ASSERT_FALSE(Coll::checkIntersection(circleBase, circleTwo));
        ASSERT_FALSE(Coll::checkIntersection(circleBase, circleThree));
        
        ASSERT_FALSE(
            Coll::checkIntersection(
                Coll::Circle(-225.5, -300.0, 100.0),
                Coll::Circle(-370.0, -360.0, 50.0)
            )
        );
    }

    TEST(CollisionChecks_Intersects_Test,
        Two_circle_arguments_which_intersect_should_return_true
        )
    {
        Coll::Circle circleBase = Coll::Circle(225.5, 300.0, 100.0);
        Coll::Circle circleOne = Coll::Circle(415.0, 350.0, 100.0);
        Coll::Circle circleTwo = Coll::Circle(365.0, 300.0, 50.0);

        ASSERT_TRUE(Coll::checkIntersection(circleBase, circleOne));
        ASSERT_TRUE(Coll::checkIntersection(circleBase, circleTwo));
        
        ASSERT_TRUE(
            Coll::checkIntersection(
                Coll::Circle(-225.5, -300.0, 100.0),
                Coll::Circle(-365.0, -300.0, 50.0)
            )
        );
    }

    TEST(CollisionChecks_Intersects_Test,
        Two_circle_arguments_sharing_an_origin_should_return_true
        )
    {
        Coll::Circle circleBase = Coll::Circle(225.5, 300.0, 100.0);
        Coll::Circle circleOne = Coll::Circle(225.5, 300.0, 100.0);
        Coll::Circle circleTwo = Coll::Circle(225.5, 300.0, 50.0);

        ASSERT_TRUE(Coll::checkIntersection(circleBase, circleOne));
        ASSERT_TRUE(Coll::checkIntersection(circleBase, circleTwo));

        ASSERT_TRUE(
            Coll::checkIntersection(
                Coll::Circle(225.5, -300.0, 100.0),
                Coll::Circle(225.5, -300.0, 50.0)
            )
        );
    }

    TEST(CollisionChecks_Intersects_Test,
        Two_aligned_rectangle_arguments_which_do_not_intersect_should_return_false
        )
    {
        Coll::Rectangle rectangleBase = Coll::Rectangle(350.0, 350.0, 300.0, 100.0);
        Coll::Rectangle rectangleOne = Coll::Rectangle(350.0, 500.0, 400.0, 100.0);
        Coll::Rectangle rectangleTwo = Coll::Rectangle(550.0, 450.0, 50.0, 50.0);
        Coll::Rectangle rectangleThree = Coll::Rectangle(550.0, 450.0, 100.0, 100.0);
        
        ASSERT_FALSE(Coll::checkIntersection(rectangleBase, rectangleOne));
        ASSERT_FALSE(Coll::checkIntersection(rectangleOne, rectangleBase));

        ASSERT_FALSE(Coll::checkIntersection(rectangleBase, rectangleTwo));
        ASSERT_FALSE(Coll::checkIntersection(rectangleTwo, rectangleBase));

        ASSERT_FALSE(Coll::checkIntersection(rectangleBase, rectangleThree));
        ASSERT_FALSE(Coll::checkIntersection(rectangleThree, rectangleBase));

        ASSERT_FALSE(
            Coll::checkIntersection(
                Coll::Rectangle(-350.0, -350.0, 300.0, 100.0), 
                Coll::Rectangle(-350.0, -500.0, 400.0, 100.0)
            )
        );
    }

    TEST(CollisionChecks_Intersects_Test,
        Two_aligned_rectangle_arguments_which_intersect_should_return_true
        )
    {
        Coll::Rectangle rectangleBase = Coll::Rectangle(350.0, 350.0, 300.0, 100.0);
        Coll::Rectangle rectangleOne = Coll::Rectangle(550.0, 450.0, 110.0, 110.0);
        Coll::Rectangle rectangleTwo = Coll::Rectangle(350.0, 500.0, 400.0, 300.0);
        Coll::Rectangle rectangleThree = Coll::Rectangle(350.0, 500.0, 100.0, 300.0);
        Coll::Rectangle rectangleFour = Coll::Rectangle(350.0, 500.0, 100.0, 600.0);
        Coll::Rectangle rectangleFive = Coll::Rectangle(550.0, 450.0, 100.1, 100.1);
        Coll::Rectangle rectangleSix = Coll::Rectangle(550.0, 450.0, 2000.0, 2000.0);

        ASSERT_TRUE(Coll::checkIntersection(rectangleBase, rectangleOne));
        ASSERT_TRUE(Coll::checkIntersection(rectangleOne, rectangleBase));

        ASSERT_TRUE(Coll::checkIntersection(rectangleBase, rectangleTwo));
        ASSERT_TRUE(Coll::checkIntersection(rectangleTwo, rectangleBase));
       
        ASSERT_TRUE(Coll::checkIntersection(rectangleBase, rectangleThree));
        ASSERT_TRUE(Coll::checkIntersection(rectangleThree, rectangleBase));
        
        ASSERT_TRUE(Coll::checkIntersection(rectangleBase, rectangleFour));
        ASSERT_TRUE(Coll::checkIntersection(rectangleFour, rectangleBase));
        
        ASSERT_TRUE(Coll::checkIntersection(rectangleBase, rectangleFive));
        ASSERT_TRUE(Coll::checkIntersection(rectangleFive, rectangleBase));
    
        ASSERT_TRUE(Coll::checkIntersection(rectangleBase, rectangleSix));
        ASSERT_TRUE(Coll::checkIntersection(rectangleSix, rectangleBase));

        ASSERT_TRUE(
            Coll::checkIntersection(
                Coll::Rectangle(-350.0, -350.0, 300.0, 100.0), 
                Coll::Rectangle(-550.0, -450.0, 110.0, 110.0)
            )
        );
    }

    TEST(CollisionChecks_Intersects_Test,
        One_aligned_rectangle_centred_within_another_aligned_rectangle_returns_true
        )
    {
        Coll::Rectangle rectangleBase = Coll::Rectangle(350.0, 350.0, 300.0, 100.0);
        Coll::Rectangle rectangleOne = Coll::Rectangle(350.0, 350.0, 310.0, 110.0);
        Coll::Rectangle rectangleTwo = Coll::Rectangle(350.0, 350.0, 290.0, 90.0);
        Coll::Rectangle rectangleThree = Coll::Rectangle(300.0, 340.0, 50.0, 50.0);
        Coll::Rectangle rectangleFour = Coll::Rectangle(300.0, 340.0, 500.0, 200.0);

        ASSERT_TRUE(Coll::checkIntersection(rectangleBase, rectangleOne));
        ASSERT_TRUE(Coll::checkIntersection(rectangleBase, rectangleTwo));

        ASSERT_TRUE(Coll::checkIntersection(rectangleBase, rectangleThree));
        ASSERT_TRUE(Coll::checkIntersection(rectangleThree, rectangleBase));
        
        ASSERT_TRUE(Coll::checkIntersection(rectangleBase, rectangleFour));
        ASSERT_TRUE(Coll::checkIntersection(rectangleFour, rectangleBase));

        ASSERT_TRUE(
            Coll::checkIntersection(
                Coll::Rectangle(-350.0, -350.0, 300.0, 100.0), 
                Coll::Rectangle(-300.0, -340.0, 400.0, 200.0)
            )
        );
    }       
}