#include "../pch.h"
//#include "../src/Collision/Circle.cpp"
#include "../../src/Collision/CollisionChecks.cpp"

namespace Coll = Collision;

namespace CollisionChecks_Tests
{
    TEST(CollisionChecks_Intersects_Circles_Test,
        Two_circle_arguments_which_do_not_intersect_should_return_false)
    {
        Coll::Circle circleBase = Coll::Circle(225.5, 300., 100.);
        Coll::Circle circleOne = Coll::Circle(425., 397.2, 100.);
        Coll::Circle circleTwo = Coll::Circle(420., 350., 100.);
        Coll::Circle circleThree = Coll::Circle(370., 360., 50.);
 
        EXPECT_FALSE(Coll::checkIntersection(circleBase, circleOne));
        EXPECT_FALSE(Coll::checkIntersection(circleBase, circleTwo));
        EXPECT_FALSE(Coll::checkIntersection(circleBase, circleThree));
        
        EXPECT_FALSE(
            Coll::checkIntersection(
                Coll::Circle(-225.5, -300., 100.),
                Coll::Circle(-370., -360., 50.)
            )
        );
    }

    TEST(CollisionChecks_Intersects_Circles_Test,
        Two_circle_arguments_which_intersect_should_return_true
        )
    {
        Coll::Circle circleBase = Coll::Circle(225.5, 300., 100.);
        Coll::Circle circleOne = Coll::Circle(415., 350., 100.);
        Coll::Circle circleTwo = Coll::Circle(365., 300., 50.);

        EXPECT_TRUE(Coll::checkIntersection(circleBase, circleOne));
        EXPECT_TRUE(Coll::checkIntersection(circleBase, circleTwo));
        
        EXPECT_TRUE(
            Coll::checkIntersection(
                Coll::Circle(-225.5, -300., 100.),
                Coll::Circle(-365., -300., 50.)
            )
        );
    }

    TEST(CollisionChecks_Intersects_Circles_Test,
        Two_circle_arguments_sharing_an_origin_should_return_true
        )
    {
        Coll::Circle circleBase = Coll::Circle(225.5, 300., 100.);
        Coll::Circle circleOne = Coll::Circle(225.5, 300., 100.);
        Coll::Circle circleTwo = Coll::Circle(225.5, 300., 50.);

        EXPECT_TRUE(Coll::checkIntersection(circleBase, circleOne));
        EXPECT_TRUE(Coll::checkIntersection(circleBase, circleTwo));

        EXPECT_TRUE(
            Coll::checkIntersection(
                Coll::Circle(225.5, -300., 100.),
                Coll::Circle(225.5, -300., 50.)
            )
        );
    }

    TEST(CollisionChecks_Intersects_Rectangles_Test,
        Two_aligned_rectangle_arguments_which_do_not_intersect_should_return_false
        )
    {
        Coll::Rectangle rectangleBase = Coll::Rectangle(350., 350., 300., 100.);
        Coll::Rectangle rectangleOne = Coll::Rectangle(350., 500., 400., 100.);
        Coll::Rectangle rectangleTwo = Coll::Rectangle(550., 450., 50., 50.);
        Coll::Rectangle rectangleThree = Coll::Rectangle(550., 450., 100., 100.);
        
        EXPECT_FALSE(Coll::checkIntersection(rectangleBase, rectangleOne));
        EXPECT_FALSE(Coll::checkIntersection(rectangleOne, rectangleBase));

        EXPECT_FALSE(Coll::checkIntersection(rectangleBase, rectangleTwo));
        EXPECT_FALSE(Coll::checkIntersection(rectangleTwo, rectangleBase));

        EXPECT_FALSE(Coll::checkIntersection(rectangleBase, rectangleThree));
        EXPECT_FALSE(Coll::checkIntersection(rectangleThree, rectangleBase));

        EXPECT_FALSE(
            Coll::checkIntersection(
                Coll::Rectangle(-350., -350., 300., 100.), 
                Coll::Rectangle(-350., -500., 400., 100.)
            )
        );
    }

    TEST(CollisionChecks_Intersects_Rectangles_Test,
        Two_aligned_rectangle_arguments_which_intersect_should_return_true
        )
    {
        Coll::Rectangle rectangleBase = Coll::Rectangle(350., 350., 300., 100.);
        Coll::Rectangle rectangleOne = Coll::Rectangle(550., 450., 110., 110.);
        Coll::Rectangle rectangleTwo = Coll::Rectangle(350., 500., 400., 300.);
        Coll::Rectangle rectangleThree = Coll::Rectangle(350., 500., 100., 300.);
        Coll::Rectangle rectangleFour = Coll::Rectangle(350., 500., 100., 600.);
        Coll::Rectangle rectangleFive = Coll::Rectangle(550., 450., 100.1, 100.1);
        Coll::Rectangle rectangleSix = Coll::Rectangle(550., 450., 2000., 2000.);

        EXPECT_TRUE(Coll::checkIntersection(rectangleBase, rectangleOne));
        EXPECT_TRUE(Coll::checkIntersection(rectangleOne, rectangleBase));

        EXPECT_TRUE(Coll::checkIntersection(rectangleBase, rectangleTwo));
        EXPECT_TRUE(Coll::checkIntersection(rectangleTwo, rectangleBase));
       
        EXPECT_TRUE(Coll::checkIntersection(rectangleBase, rectangleThree));
        EXPECT_TRUE(Coll::checkIntersection(rectangleThree, rectangleBase));
        
        EXPECT_TRUE(Coll::checkIntersection(rectangleBase, rectangleFour));
        EXPECT_TRUE(Coll::checkIntersection(rectangleFour, rectangleBase));
        
        EXPECT_TRUE(Coll::checkIntersection(rectangleBase, rectangleFive));
        EXPECT_TRUE(Coll::checkIntersection(rectangleFive, rectangleBase));
    
        EXPECT_TRUE(Coll::checkIntersection(rectangleBase, rectangleSix));
        EXPECT_TRUE(Coll::checkIntersection(rectangleSix, rectangleBase));

        EXPECT_TRUE(
            Coll::checkIntersection(
                Coll::Rectangle(-350., -350., 300., 100.), 
                Coll::Rectangle(-550., -450., 110., 110.)
            )
        );
    }

    TEST(CollisionChecks_Intersects_Rectangles_Test,
        One_aligned_rectangle_centred_within_another_aligned_rectangle_returns_true
        )
    {
        Coll::Rectangle rectangleBase = Coll::Rectangle(350., 350., 300., 100.);
        Coll::Rectangle rectangleOne = Coll::Rectangle(350., 350., 310., 110.);
        Coll::Rectangle rectangleTwo = Coll::Rectangle(350., 350., 290., 90.);
        Coll::Rectangle rectangleThree = Coll::Rectangle(300., 340., 50., 50.);
        Coll::Rectangle rectangleFour = Coll::Rectangle(300., 340., 500., 200.);

        EXPECT_TRUE(Coll::checkIntersection(rectangleBase, rectangleOne));
        EXPECT_TRUE(Coll::checkIntersection(rectangleBase, rectangleTwo));

        EXPECT_TRUE(Coll::checkIntersection(rectangleBase, rectangleThree));
        EXPECT_TRUE(Coll::checkIntersection(rectangleThree, rectangleBase));
        
        EXPECT_TRUE(Coll::checkIntersection(rectangleBase, rectangleFour));
        EXPECT_TRUE(Coll::checkIntersection(rectangleFour, rectangleBase));

        EXPECT_TRUE(
            Coll::checkIntersection(
                Coll::Rectangle(-350., -350., 300., 100.), 
                Coll::Rectangle(-300., -340., 400., 200.)
            )
        );
    }

    TEST(CollisionChecks_Intersects_Rectangles_Test,
        One_aligned_and_one_unaligned_rectangle_which_do_not_intersect_returns_false
    )
    {
        Coll::Rectangle rectangleBase = Coll::Rectangle(750., 675., 500., 150.);
        Coll::Rectangle rectangleOne = Coll::Rectangle(1100., 750., 100., 300.);

        Coll::Rectangle rectangleTwo = Coll::Rectangle(-750., -675., 500., 150.);
        Coll::Rectangle rectangleThree = Coll::Rectangle(-1100., -750., 100., 300.);

        rectangleBase.setAngle(20);
        rectangleTwo.setAngle(20);
        
        EXPECT_FALSE(Coll::checkIntersection(rectangleBase, rectangleOne));
        EXPECT_FALSE(Coll::checkIntersection(rectangleOne, rectangleBase));

        EXPECT_FALSE(Coll::checkIntersection(rectangleTwo, rectangleThree));
        EXPECT_FALSE(Coll::checkIntersection(rectangleThree, rectangleTwo));
    }

    TEST(CollisionChecks_Intersects_Rectangles_Test,
        One_aligned_and_one_unaligned_rectangle_which_intersect_returns_true
    )
    {
        Coll::Rectangle rectangleBase = Coll::Rectangle(750., 675., 500., 150.);
        Coll::Rectangle rectangleOne = Coll::Rectangle(1100., 750., 100., 300.);

        Coll::Rectangle rectangleTwo = Coll::Rectangle(-750., -675., 500., 150.);
        Coll::Rectangle rectangleThree = Coll::Rectangle(-1100., -750., 100., 300.);
        
        rectangleOne.setAngle(70.);
        rectangleThree.setAngle(70.);

        EXPECT_TRUE(Coll::checkIntersection(rectangleBase, rectangleOne));
        EXPECT_TRUE(Coll::checkIntersection(rectangleOne, rectangleBase));

        EXPECT_TRUE(Coll::checkIntersection(rectangleTwo, rectangleThree));
        EXPECT_TRUE(Coll::checkIntersection(rectangleThree, rectangleTwo));
    }

    TEST(CollisionChecks_Intersects_Rectangles_Test,
        Two_unaligned_rectangles_which_do_not_intersect_returns_false
    )
    {
        Coll::Rectangle rectangleBase = Coll::Rectangle(750., 675., 500., 150.);
        Coll::Rectangle rectangleOne = Coll::Rectangle(1100., 750., 100., 300.);
        Coll::Rectangle rectangleTwo = Coll::Rectangle(900., 780., 100., 300.);

        Coll::Rectangle rectangleThree = Coll::Rectangle(-750., -675., 500., 150.);
        Coll::Rectangle rectangleFour = Coll::Rectangle(-1100., -750., 100., 300.);

        rectangleBase.setAngle(350.);
        rectangleOne.setAngle(70.);
        rectangleTwo.setAngle(80.);
        rectangleThree.setAngle(350.);
        rectangleFour.setAngle(70.);

        EXPECT_FALSE(Coll::checkIntersection(rectangleBase, rectangleOne));
        EXPECT_FALSE(Coll::checkIntersection(rectangleOne, rectangleBase));

        EXPECT_FALSE(Coll::checkIntersection(rectangleBase, rectangleTwo));
        EXPECT_FALSE(Coll::checkIntersection(rectangleTwo, rectangleBase));

        EXPECT_FALSE(Coll::checkIntersection(rectangleThree, rectangleFour));
        EXPECT_FALSE(Coll::checkIntersection(rectangleFour, rectangleThree));          
    }

    TEST(CollisionChecks_Intersects_Rectangles_Test,
        Two_unaligned_rectangles_which_intersect_returns_true
    )
    {
        Coll::Rectangle rectangleBase = Coll::Rectangle(750., 675., 500., 150.);
        Coll::Rectangle rectangleOne = Coll::Rectangle(1100., 750., 100., 300.);
        Coll::Rectangle rectangleTwo = Coll::Rectangle(900., 780., 100., 300.);

        Coll::Rectangle rectangleThree = Coll::Rectangle(-750., -675., 500., 150.);
        Coll::Rectangle rectangleFour = Coll::Rectangle(-1100., -750., 100., 300.);

        rectangleBase.setAngle(20.);
        rectangleOne.setAngle(70.);
        rectangleTwo.setAngle(170.);

        rectangleThree.setAngle(20.);
        rectangleFour.setAngle(70.);

        EXPECT_TRUE(Coll::checkIntersection(rectangleBase, rectangleOne));
        EXPECT_TRUE(Coll::checkIntersection(rectangleOne, rectangleBase));

        rectangleBase.setAngle(350.);
        EXPECT_TRUE(Coll::checkIntersection(rectangleBase, rectangleTwo));
        EXPECT_TRUE(Coll::checkIntersection(rectangleTwo, rectangleBase));

        EXPECT_FALSE(Coll::checkIntersection(rectangleThree, rectangleFour));
        EXPECT_FALSE(Coll::checkIntersection(rectangleFour, rectangleThree));
    }

    TEST(CollisionChecks_Intersects_Rectangle_Circle_Test,
        An_aligned_rectangle_and_a_circle_which_do_not_intersect_returns_false
    )
    {
        Coll::Rectangle rectangleBase = Coll::Rectangle(750.f, 675.f, 500.f, 150.f);
        Coll::Circle circleOne = Coll::Circle(850.f, 810.f, 50.f);
        Coll::Circle circleTwo = Coll::Circle(430.f, 670.f, 50.f);
        Coll::Circle circleThree = Coll::Circle(450.f, 550.f, 50.f);
        Coll::Circle circleFour = Coll::Circle(1050.f, 780.f, 50.f);

        EXPECT_FALSE(Coll::checkIntersection(rectangleBase, circleOne));
        EXPECT_FALSE(Coll::checkIntersection(rectangleBase, circleTwo));
        EXPECT_FALSE(Coll::checkIntersection(rectangleBase, circleThree));
        EXPECT_FALSE(Coll::checkIntersection(rectangleBase, circleFour));
    
        Coll::Rectangle rectangleOne = Coll::Rectangle(-750.f, -675.f, 500.f, 150.f);
        Coll::Circle circleFive = Coll::Circle(-450.f, -550.f, 50.f);
        Coll::Circle circleSix = Coll::Circle(-1050.f, -780.f, 50.f);
    
        EXPECT_FALSE(Coll::checkIntersection(rectangleOne, circleFive));
        EXPECT_FALSE(Coll::checkIntersection(rectangleOne, circleSix));
    }

    TEST(CollisionChecks_Intersects_Rectangle_Circle_Test,
        An_aligned_rectangle_and_a_circle_which_intersect_returns_true
    )
    {
        Coll::Rectangle rectangleBase = Coll::Rectangle(750.f, 675.f, 500.f, 150.f);
        Coll::Circle circleOne = Coll::Circle(850.f, 740.f, 50.f);
        Coll::Circle circleTwo = Coll::Circle(460.f, 670.f, 50.f);
        Coll::Circle circleThree = Coll::Circle(480.f, 580.f, 50.f);
        Coll::Circle circleFour = Coll::Circle(1030.f, 770.f, 50.f);
        Coll::Circle circleFive = Coll::Circle(560.f, 670.f, 50.f);
        Coll::Circle circleSix = Coll::Circle(1050.f, 780.f, 50.f);

        EXPECT_TRUE(Coll::checkIntersection(rectangleBase, circleOne));
        EXPECT_TRUE(Coll::checkIntersection(rectangleBase, circleTwo));
        EXPECT_TRUE(Coll::checkIntersection(rectangleBase, circleThree));
        EXPECT_TRUE(Coll::checkIntersection(rectangleBase, circleFour));
        EXPECT_TRUE(Coll::checkIntersection(rectangleBase, circleFive));
        EXPECT_TRUE(Coll::checkIntersection(rectangleBase, circleSix));

        Coll::Rectangle rectangleOne = Coll::Rectangle(-750.f, -675.f, 500.f, 150.f);
        Coll::Circle circleSeven = Coll::Circle(-480.f, -580.f, 50.f);
        Coll::Circle circleEight = Coll::Circle(-1030.f, -770.f, 50.f);

        EXPECT_TRUE(Coll::checkIntersection(rectangleOne, circleSeven));
        EXPECT_TRUE(Coll::checkIntersection(rectangleOne, circleEight));

    
    
    }

    TEST(CollisionChecks_Intersects_Rectangle_Circle_Test,
        An_unaligned_rectangle_and_a_circle_which_do_not_intersect_returns_false
    )
    {
        Coll::Rectangle rectangleBase = Coll::Rectangle(750.f, 675.f, 500.f, 150.f);
        rectangleBase.setAngle(30.f);

        Coll::Circle circleOne = Coll::Circle(680.f, 810.f, 50.f);
        Coll::Circle circleTwo = Coll::Circle(480.f, 520.f, 50.f);
        Coll::Circle circleThree = Coll::Circle(550.f, 430.f, 50.f);
        Coll::Circle circleFour = Coll::Circle(940.f, 930.f, 50.f);

        EXPECT_FALSE(Coll::checkIntersection(rectangleBase, circleOne));
        EXPECT_FALSE(Coll::checkIntersection(rectangleBase, circleTwo));
        EXPECT_FALSE(Coll::checkIntersection(rectangleBase, circleThree));
        EXPECT_FALSE(Coll::checkIntersection(rectangleBase, circleFour));
    

        Coll::Rectangle rectangleOne = Coll::Rectangle(-750.f, -675.f, 500.f, 150.f);
        rectangleOne.setAngle(30.f);
        Coll::Circle circleFive = Coll::Circle(-550.f, -430.f, 50.f);
        Coll::Circle circleSix = Coll::Circle(-940.f, -930.f, 50.f);
    
        EXPECT_FALSE(Coll::checkIntersection(rectangleOne, circleFive));
        EXPECT_FALSE(Coll::checkIntersection(rectangleOne, circleSix));

    }

    TEST(CollisionChecks_Intersects_Rectangle_Circle_Test,
        An_unaligned_rectangle_and_a_circle_which_intersect_returns_true
    )
    {
        Coll::Rectangle rectangleBase = Coll::Rectangle(750.f, 675.f, 500.f, 150.f);
        rectangleBase.setAngle(30.f);
    
        Coll::Circle circleOne = Coll::Circle(690.f, 770.f, 50.f);
        Coll::Circle circleTwo = Coll::Circle(500.f, 530.f, 50.f);
        Coll::Circle circleThree = Coll::Circle(570.f, 450.f, 50.f);
        Coll::Circle circleFour = Coll::Circle(920.f, 900.f, 50.f);
        Coll::Circle circleFive = Coll::Circle(610.f, 590.f, 50.f);
        Coll::Circle circleSix = Coll::Circle(750.f, 700.f, 50.f);

        EXPECT_TRUE(Coll::checkIntersection(rectangleBase, circleOne));
        EXPECT_TRUE(Coll::checkIntersection(rectangleBase, circleTwo));
        EXPECT_TRUE(Coll::checkIntersection(rectangleBase, circleThree));
        EXPECT_TRUE(Coll::checkIntersection(rectangleBase, circleFour));
        EXPECT_TRUE(Coll::checkIntersection(rectangleBase, circleFive));
        EXPECT_TRUE(Coll::checkIntersection(rectangleBase, circleSix));

        Coll::Rectangle rectangleOne = Coll::Rectangle(-750.f, -675.f, 500.f, 150.f);
        rectangleOne.setAngle(30.f);
        Coll::Circle circleSeven = Coll::Circle(-570.f, -450.f, 50.f);
        Coll::Circle circleEight = Coll::Circle(-920.f, -900.f, 50.f);

        EXPECT_TRUE(Coll::checkIntersection(rectangleOne, circleSeven));
        EXPECT_TRUE(Coll::checkIntersection(rectangleOne, circleEight));

    }

    TEST(CollisionChecks_Intersects_Rectangle_Circle_Test,
        An_unaligned_310_rectangle_and_a_circle_which_do_not_intersect_returns_false
    )
    {
        Coll::Rectangle rectangleBase = Coll::Rectangle(750.f, 675.f, 500.f, 150.f);
        rectangleBase.setAngle(310.f);

        Coll::Circle circleOne = Coll::Circle(850.f, 770.f, 50.f);
        Coll::Circle circleTwo = Coll::Circle(530.f, 910.f, 50.f);
        Coll::Circle circleThree = Coll::Circle(470.f, 830.f, 50.f);
        Coll::Circle circleFour = Coll::Circle(1030.f, 530.f, 50.f);

        EXPECT_FALSE(Coll::checkIntersection(rectangleBase, circleOne));
        EXPECT_FALSE(Coll::checkIntersection(rectangleBase, circleTwo));
        EXPECT_FALSE(Coll::checkIntersection(rectangleBase, circleThree));
        EXPECT_FALSE(Coll::checkIntersection(rectangleBase, circleFour));
    

        Coll::Rectangle rectangleOne = Coll::Rectangle(-750.f, -675.f, 500.f, 150.f);
        rectangleOne.setAngle(310.f);
        Coll::Circle circleFive = Coll::Circle(-470.f, -830.f, 50.f);
        Coll::Circle circleSix = Coll::Circle(-1030.f, -530.f, 50.f);

        EXPECT_FALSE(Coll::checkIntersection(rectangleOne, circleFive));
        EXPECT_FALSE(Coll::checkIntersection(rectangleOne, circleSix));
    }

    TEST(CollisionChecks_Intersects_Rectangle_Circle_Test,
        An_unaligned_310_rectangle_and_a_circle_which_intersect_returns_true
    )
    {
        Coll::Rectangle rectangleBase = Coll::Rectangle(750.f, 675.f, 500.f, 150.f);
        rectangleBase.setAngle(310.f);

        Coll::Circle circleOne = Coll::Circle(830.f, 750.f, 50.f);
        Coll::Circle circleTwo = Coll::Circle(550.f, 890.f, 50.f);
        Coll::Circle circleThree = Coll::Circle(490.f, 820.f, 50.f);
        Coll::Circle circleFour = Coll::Circle(1010.f, 520.f, 50.f);
        Coll::Circle circleFive = Coll::Circle(630.f, 810.f, 50.f);
        Coll::Circle circleSix = Coll::Circle(750.f, 700.f, 50.f);
    
        EXPECT_TRUE(Coll::checkIntersection(rectangleBase, circleOne));
        EXPECT_TRUE(Coll::checkIntersection(rectangleBase, circleTwo));
        EXPECT_TRUE(Coll::checkIntersection(rectangleBase, circleThree));
        EXPECT_TRUE(Coll::checkIntersection(rectangleBase, circleFour));
        EXPECT_TRUE(Coll::checkIntersection(rectangleBase, circleFive));
        EXPECT_TRUE(Coll::checkIntersection(rectangleBase, circleSix));

        Coll::Rectangle rectangleOne = Coll::Rectangle(-750.f, -675.f, 500.f, 150.f);
        rectangleOne.setAngle(310.f);
        Coll::Circle circleSeven = Coll::Circle(-490.f, -820.f, 50.f);
        Coll::Circle circleEight = Coll::Circle(-1010.f, -520.f, 50.f);
        
        EXPECT_TRUE(Coll::checkIntersection(rectangleBase, circleSeven));
        EXPECT_TRUE(Coll::checkIntersection(rectangleBase, circleEight));
    

    }
}