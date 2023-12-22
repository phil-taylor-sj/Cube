#include "../pch.h"
#include "Collision/CollisionChecks.h"
#include "Collision/CollisionComponents.h"

namespace Coll = Collision;

namespace CollisionChecks_Tests
{
    TEST(CollisionChecks_Intersects_Circles_Test,
        Two_circle_arguments_which_do_not_intersect_should_return_false)
    {
        Coll::CircleComponent circleBase = Coll::CircleComponent();
        circleBase.x = 225.5f;
        circleBase.y = 300.f;
        circleBase.radius = 100.f;
        
        Coll::CircleComponent circleOne = Coll::CircleComponent();
        circleOne.x = 425.f;
        circleOne.y = 397.2f;
        circleOne.radius = 100.f;

        Coll::CircleComponent circleTwo = Coll::CircleComponent();
        circleTwo.x = 420.f;
        circleTwo.y = 350.f;
        circleTwo.radius = 100.f;

        Coll::CircleComponent circleThree = Coll::CircleComponent();
        circleThree.x = 370.f;
        circleThree.y = 360.f;
        circleThree.radius = 50.f;
 
        EXPECT_FALSE(Coll::checkIntersection(circleBase, circleOne));
        EXPECT_FALSE(Coll::checkIntersection(circleBase, circleTwo));
        EXPECT_FALSE(Coll::checkIntersection(circleBase, circleThree));
        
        Coll::CircleComponent circleFour = Coll::CircleComponent();
        circleFour.x = -225.5f;
        circleFour.y = -300.f;
        circleFour.radius = 100.f;

        Coll::CircleComponent circleFive = Coll::CircleComponent();
        circleFive.x = -370.f;
        circleFive.y = -360.f;
        circleFive.radius = 50.f;

        EXPECT_FALSE(Coll::checkIntersection(circleFour, circleFive));
    }

    TEST(CollisionChecks_Intersects_Circles_Test,
        Two_circle_arguments_which_intersect_should_return_true
        )
    {
        Coll::CircleComponent circleBase = Coll::CircleComponent();
        circleBase.x = 225.5f;
        circleBase.y = 300.f;
        circleBase.radius = 100.f;
        
        Coll::CircleComponent circleOne = Coll::CircleComponent();
        circleOne.x = 415.f; 
        circleOne.y = 350.f; 
        circleOne.radius = 100.f;

        Coll::CircleComponent circleTwo = Coll::CircleComponent();
        circleTwo.x = 365.f;
        circleTwo.y = 300.f;
        circleTwo.radius = 50.f;

        EXPECT_TRUE(Coll::checkIntersection(circleBase, circleOne));
        EXPECT_TRUE(Coll::checkIntersection(circleBase, circleTwo));
        
        Coll::CircleComponent circleThree = Coll::CircleComponent();
        circleThree.x = -225.5f;
        circleThree.y = -300.f; 
        circleThree.radius = 100.f;

        Coll::CircleComponent circleFour = Coll::CircleComponent();
        circleFour.x = -365.f;
        circleFour.y = -300.f;
        circleFour.radius = 50.f;
        
        EXPECT_TRUE(Coll::checkIntersection(circleThree, circleFour));
    }

    TEST(CollisionChecks_Intersects_Circles_Test,
        Two_circle_arguments_sharing_an_origin_should_return_true
        )
    {
        Coll::CircleComponent circleBase = Coll::CircleComponent();
        circleBase.x = 225.5f;
        circleBase.y = 300.f;
        circleBase.radius = 100.f;
        
        Coll::CircleComponent circleOne = Coll::CircleComponent();
        circleOne.x = 225.5f;
        circleOne.y = 300.f;
        circleOne.radius = 100.f;
        
        Coll::CircleComponent circleTwo = Coll::CircleComponent();
        circleTwo.x = 225.5f;
        circleTwo.y = 300.f;
        circleTwo.radius = 50.f;

        EXPECT_TRUE(Coll::checkIntersection(circleBase, circleOne));
        EXPECT_TRUE(Coll::checkIntersection(circleBase, circleTwo));

        Coll::CircleComponent circleThree = Coll::CircleComponent();
        circleThree.x = 225.5f;
        circleThree.y = -300.f;
        circleThree.radius = 100.f;

        Coll::CircleComponent circleFour = Coll::CircleComponent();
        circleFour.x = 225.5f;
        circleFour.y = -300.f;
        circleFour.radius = 50.f;

        EXPECT_TRUE(Coll::checkIntersection(circleThree, circleFour));
    }

    TEST(CollisionChecks_Intersects_Rectangles_Test,
        Two_aligned_rectangle_arguments_which_do_not_intersect_should_return_false
        )
    {
        Coll::RectComponent rectangleBase = Coll::RectComponent();
        rectangleBase.x = 350.f;
        rectangleBase.y = 350.f;
        rectangleBase.width = 300.f;
        rectangleBase.height =100.f;

        Coll::RectComponent rectangleOne = Coll::RectComponent();
        rectangleOne.x = 350.f;
        rectangleOne.y = 500.f;
        rectangleOne.width = 400.f;
        rectangleOne.height = 100.f;

        Coll::RectComponent rectangleTwo = Coll::RectComponent();
        rectangleTwo.x = 550.f;
        rectangleTwo.y = 450.f;
        rectangleTwo.width = 50.f;
        rectangleTwo.height = 50.f;

        Coll::RectComponent rectangleThree = Coll::RectComponent();
        rectangleThree.x = 550.f;
        rectangleThree.y = 450.f;
        rectangleThree.width = 100.f;
        rectangleThree.height = 100.f;
        
        EXPECT_FALSE(Coll::checkIntersection(rectangleBase, rectangleOne));
        EXPECT_FALSE(Coll::checkIntersection(rectangleOne, rectangleBase));

        EXPECT_FALSE(Coll::checkIntersection(rectangleBase, rectangleTwo));
        EXPECT_FALSE(Coll::checkIntersection(rectangleTwo, rectangleBase));

        EXPECT_FALSE(Coll::checkIntersection(rectangleBase, rectangleThree));
        EXPECT_FALSE(Coll::checkIntersection(rectangleThree, rectangleBase));

        Coll::RectComponent rectangleFour = Coll::RectComponent();
        rectangleFour.x = -350.f;
        rectangleFour.y = -350.f;
        rectangleFour.width = 300.f;
        rectangleFour.height = 100.f;

        Coll::RectComponent rectangleFive = Coll::RectComponent();
        rectangleFive.x = -350.f;
        rectangleFive.y = -500.f;
        rectangleFive.width = 400.f;
        rectangleFive.height = 100.f;

        EXPECT_FALSE(Coll::checkIntersection(rectangleFour, rectangleFive));
    }

    TEST(CollisionChecks_Intersects_Rectangles_Test,
        Two_aligned_rectangle_arguments_which_intersect_should_return_true
        )
    {
        Coll::RectComponent rectangleBase = Coll::RectComponent();
        rectangleBase.x = 350.f;
        rectangleBase.y = 350.f;
        rectangleBase.width = 300.f;
        rectangleBase.height = 100.f;

        Coll::RectComponent rectangleOne = Coll::RectComponent();
        rectangleOne.x = 550.f;
        rectangleOne.y = 450.f;
        rectangleOne.width = 110.f;
        rectangleOne.height = 110.f;

        Coll::RectComponent rectangleTwo = Coll::RectComponent();
        rectangleTwo.x = 350.f;
        rectangleTwo.y = 500.f;
        rectangleTwo.width = 400.f;
        rectangleTwo.height = 300.f;

        Coll::RectComponent rectangleThree = Coll::RectComponent();
        rectangleThree.x = 350.f;
        rectangleThree.y = 500.f;
        rectangleThree.width = 100.f;
        rectangleThree.height = 300.f;

        Coll::RectComponent rectangleFour = Coll::RectComponent();
        rectangleFour.x = 350.f;
        rectangleFour.y = 500.f;
        rectangleFour.width = 100.f;
        rectangleFour.height = 600.f;

        Coll::RectComponent rectangleFive = Coll::RectComponent();
        rectangleFour.x = 550.f;
        rectangleFour.y = 450.f;
        rectangleFour.width = 100.1f;
        rectangleFour.height = 100.1f;

        Coll::RectComponent rectangleSix = Coll::RectComponent();
        rectangleFive.x = 550.f;
        rectangleFive.y = 450.f;
        rectangleFive.width = 2000.f;
        rectangleFive.height = 2000.f;

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

        Coll::RectComponent rectangleSeven = Coll::RectComponent();
        rectangleSeven.x = -350.f;
        rectangleSeven.y = -350.f;
        rectangleSeven.width = 300.f;
        rectangleSeven.height = 100.f;

        Coll::RectComponent rectangleEight = Coll::RectComponent();
        rectangleEight.x = -550.f;
        rectangleEight.y = -450.f;
        rectangleEight.width = 110.f;
        rectangleEight.height = 110.f;

        EXPECT_TRUE(Coll::checkIntersection(rectangleSeven, rectangleEight));
    }

    TEST(CollisionChecks_Intersects_Rectangles_Test,
        One_aligned_rectangle_centred_within_another_aligned_rectangle_returns_true
        )
    {
        Coll::RectComponent rectangleBase = Coll::RectComponent();
        rectangleBase.x = 350.f;
        rectangleBase.y = 350.f;
        rectangleBase.width = 300.f;
        rectangleBase.height = 100.f;

        Coll::RectComponent rectangleOne = Coll::RectComponent();
        rectangleOne.x = 350.f;
        rectangleOne.y = 350.f;
        rectangleOne.width = 310.f;
        rectangleOne.height = 110.f;

        Coll::RectComponent rectangleTwo = Coll::RectComponent();
        rectangleTwo.x = 350.f;
        rectangleTwo.y = 350.f;
        rectangleTwo.width = 290.f;
        rectangleTwo.height = 90.f;

        Coll::RectComponent rectangleThree = Coll::RectComponent();
        rectangleThree.x = 300.f;
        rectangleThree.y = 340.f;
        rectangleThree.width = 50.f;
        rectangleThree.height = 50.f;

        Coll::RectComponent rectangleFour = Coll::RectComponent();
        rectangleFour.x = 300.f;
        rectangleFour.y = 340.f;
        rectangleFour.width = 500.f;
        rectangleFour.height = 200.f;

        EXPECT_TRUE(Coll::checkIntersection(rectangleBase, rectangleOne));
        EXPECT_TRUE(Coll::checkIntersection(rectangleBase, rectangleTwo));

        EXPECT_TRUE(Coll::checkIntersection(rectangleBase, rectangleThree));
        EXPECT_TRUE(Coll::checkIntersection(rectangleThree, rectangleBase));
        
        EXPECT_TRUE(Coll::checkIntersection(rectangleBase, rectangleFour));
        EXPECT_TRUE(Coll::checkIntersection(rectangleFour, rectangleBase));

        Coll::RectComponent rectangleFive = Coll::RectComponent();
        rectangleFive.x = -350.f;
        rectangleFive.y = -350.f;
        rectangleFive.width = 300.f;
        rectangleFive.height = 100.f;

        Coll::RectComponent rectangleSix = Coll::RectComponent();
        rectangleSix.x = -300.f;
        rectangleSix.y = -340.f;
        rectangleSix.width = 400.f;
        rectangleSix.height = 200.f;

        EXPECT_TRUE(Coll::checkIntersection(rectangleFive, rectangleSix));
    }

    TEST(CollisionChecks_Intersects_Rectangles_Test,
        One_aligned_and_one_unaligned_rectangle_which_do_not_intersect_returns_false
    )
    {
        Coll::RectComponent rectangleBase = Coll::RectComponent(750., 675., 500., 150.);
        Coll::RectComponent rectangleOne = Coll::RectComponent(1100., 750., 100., 300.);

        Coll::RectComponent rectangleTwo = Coll::RectComponent(-750., -675., 500., 150.);
        Coll::RectComponent rectangleThree = Coll::RectComponent(-1100., -750., 100., 300.);

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
        Coll::RectComponent rectangleBase = Coll::RectComponent(750., 675., 500., 150.);
        Coll::RectComponent rectangleOne = Coll::RectComponent(1100., 750., 100., 300.);

        Coll::RectComponent rectangleTwo = Coll::RectComponent(-750., -675., 500., 150.);
        Coll::RectComponent rectangleThree = Coll::RectComponent(-1100., -750., 100., 300.);
        
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
        Coll::RectComponent rectangleBase = Coll::RectComponent();
        rectangleBase.x = 750.f;
        rectangleBase.y = 675.f;
        rectangleBase.width = 500.f;
        rectangleBase.height = 150.f;
        rectangleBase.angle = 350.f;

        Coll::RectComponent rectangleOne = Coll::RectComponent();
        rectangleOne.x = 1100.f;
        rectangleOne.y = 750.f;
        rectangleOne.width = 100.f;
        rectangleOne.height = 300.f;
        rectangleOne.angle = 70.f;

        Coll::RectComponent rectangleTwo = Coll::RectComponent();
        rectangleTwo.x = 900.f;
        rectangleTwo.y = 780.f;
        rectangleTwo.width = 100.f;
        rectangleTwo.height = 300.f;
        rectangleTwo.angle = 80.f;


        Coll::RectComponent rectangleThree = Coll::RectComponent();
        rectangleThree.x = -750.f;
        rectangleThree.y = -675.f;
        rectangleThree.width = 500.f;
        rectangleThree.height = 150.f;
        rectangleThree.angle = 350.f;

        Coll::RectComponent rectangleFour = Coll::RectComponent();
        rectangleFour.x = -1100.f;
        rectangleFour.y = -750.f;
        rectangleFour.width = 100.f;
        rectangleFour.height = 300.f;
        rectangleFour.angle = 70.f;

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
        Coll::RectComponent rectangleBase = Coll::RectComponent(750., 675., 500., 150.);
        Coll::RectComponent rectangleOne = Coll::RectComponent(1100., 750., 100., 300.);
        Coll::RectComponent rectangleTwo = Coll::RectComponent(900., 780., 100., 300.);

        Coll::RectComponent rectangleThree = Coll::RectComponent(-750., -675., 500., 150.);
        Coll::RectComponent rectangleFour = Coll::RectComponent(-1100., -750., 100., 300.);

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

        EXPECT_TRUE(Coll::checkIntersection(rectangleThree, rectangleFour));
        EXPECT_TRUE(Coll::checkIntersection(rectangleFour, rectangleThree));
    }

    TEST(CollisionChecks_Intersects_Rectangle_Circle_Test,
        An_aligned_rectangle_and_a_circle_which_do_not_intersect_returns_false
    )
    {
        Coll::RectComponent rectangleBase = Coll::RectComponent(750.f, 675.f, 500.f, 150.f);
        Coll::Circle circleOne = Coll::Circle(850.f, 810.f, 50.f);
        Coll::Circle circleTwo = Coll::Circle(430.f, 670.f, 50.f);
        Coll::Circle circleThree = Coll::Circle(450.f, 550.f, 50.f);
        Coll::Circle circleFour = Coll::Circle(1050.f, 780.f, 50.f);

        EXPECT_FALSE(Coll::checkIntersection(rectangleBase, circleOne));
        EXPECT_FALSE(Coll::checkIntersection(rectangleBase, circleTwo));
        EXPECT_FALSE(Coll::checkIntersection(rectangleBase, circleThree));
        EXPECT_FALSE(Coll::checkIntersection(rectangleBase, circleFour));
    
        Coll::RectComponent rectangleOne = Coll::RectComponent(-750.f, -675.f, 500.f, 150.f);
        Coll::Circle circleFive = Coll::Circle(-450.f, -550.f, 50.f);
        Coll::Circle circleSix = Coll::Circle(-1050.f, -780.f, 50.f);
    
        EXPECT_FALSE(Coll::checkIntersection(rectangleOne, circleFive));
        EXPECT_FALSE(Coll::checkIntersection(rectangleOne, circleSix));
    }

    TEST(CollisionChecks_Intersects_Rectangle_Circle_Test,
        An_aligned_rectangle_and_a_circle_which_intersect_returns_true
    )
    {
        Coll::RectComponent rectangleBase = Coll::RectComponent(750.f, 675.f, 500.f, 150.f);
        Coll::Circle circleOne = Coll::Circle(850.f, 740.f, 50.f);
        Coll::Circle circleTwo = Coll::Circle(460.f, 670.f, 50.f);
        Coll::Circle circleThree = Coll::Circle(480.f, 580.f, 50.f);
        Coll::Circle circleFour = Coll::Circle(1030.f, 770.f, 50.f);
        Coll::Circle circleFive = Coll::Circle(560.f, 670.f, 50.f);
        Coll::Circle circleSix = Coll::Circle(750.f, 700.f, 50.f);

        EXPECT_TRUE(Coll::checkIntersection(rectangleBase, circleOne));
        EXPECT_TRUE(Coll::checkIntersection(rectangleBase, circleTwo));
        EXPECT_TRUE(Coll::checkIntersection(rectangleBase, circleThree));
        EXPECT_TRUE(Coll::checkIntersection(rectangleBase, circleFour));
        EXPECT_TRUE(Coll::checkIntersection(rectangleBase, circleFive));
        EXPECT_TRUE(Coll::checkIntersection(rectangleBase, circleSix));

        Coll::RectComponent rectangleOne = Coll::RectComponent(-750.f, -675.f, 500.f, 150.f);
        Coll::Circle circleSeven = Coll::Circle(-480.f, -580.f, 50.f);
        Coll::Circle circleEight = Coll::Circle(-1030.f, -770.f, 50.f);

        EXPECT_TRUE(Coll::checkIntersection(rectangleOne, circleSeven));
        EXPECT_TRUE(Coll::checkIntersection(rectangleOne, circleEight));

    
    
    }

    TEST(CollisionChecks_Intersects_Rectangle_Circle_Test,
        An_unaligned_rectangle_and_a_circle_which_do_not_intersect_returns_false
    )
    {
        Coll::RectComponent rectangleBase = Coll::RectComponent(750.f, 675.f, 500.f, 150.f);
        rectangleBase.setAngle(30.f);

        Coll::Circle circleOne = Coll::Circle(680.f, 810.f, 50.f);
        Coll::Circle circleTwo = Coll::Circle(480.f, 520.f, 50.f);
        Coll::Circle circleThree = Coll::Circle(550.f, 430.f, 50.f);
        Coll::Circle circleFour = Coll::Circle(940.f, 930.f, 50.f);

        EXPECT_FALSE(Coll::checkIntersection(rectangleBase, circleOne));
        EXPECT_FALSE(Coll::checkIntersection(rectangleBase, circleTwo));
        EXPECT_FALSE(Coll::checkIntersection(rectangleBase, circleThree));
        EXPECT_FALSE(Coll::checkIntersection(rectangleBase, circleFour));
    

        Coll::RectComponent rectangleOne = Coll::RectComponent(-750.f, -675.f, 500.f, 150.f);
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
        Coll::RectComponent rectangleBase = Coll::RectComponent(750.f, 675.f, 500.f, 150.f);
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

        Coll::RectComponent rectangleOne = Coll::RectComponent(-750.f, -675.f, 500.f, 150.f);
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
        Coll::RectComponent rectangleBase = Coll::RectComponent(750.f, 675.f, 500.f, 150.f);
        rectangleBase.setAngle(310.f);

        Coll::Circle circleOne = Coll::Circle(850.f, 770.f, 50.f);
        Coll::Circle circleTwo = Coll::Circle(530.f, 910.f, 50.f);
        Coll::Circle circleThree = Coll::Circle(470.f, 830.f, 50.f);
        Coll::Circle circleFour = Coll::Circle(1030.f, 530.f, 50.f);

        EXPECT_FALSE(Coll::checkIntersection(rectangleBase, circleOne));
        EXPECT_FALSE(Coll::checkIntersection(rectangleBase, circleTwo));
        EXPECT_FALSE(Coll::checkIntersection(rectangleBase, circleThree));
        EXPECT_FALSE(Coll::checkIntersection(rectangleBase, circleFour));
    

        Coll::RectComponent rectangleOne = Coll::RectComponent(-750.f, -675.f, 500.f, 150.f);
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
        Coll::RectComponent rectangleBase = Coll::RectComponent(750.f, 675.f, 500.f, 150.f);
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

        Coll::RectComponent rectangleOne = Coll::RectComponent(-750.f, -675.f, 500.f, 150.f);
        rectangleOne.setAngle(310.f);
        Coll::Circle circleSeven = Coll::Circle(-490.f, -820.f, 50.f);
        Coll::Circle circleEight = Coll::Circle(-1010.f, -520.f, 50.f);
        
        EXPECT_TRUE(Coll::checkIntersection(rectangleOne, circleSeven));
        EXPECT_TRUE(Coll::checkIntersection(rectangleOne, circleEight));
    }

    TEST(CollisionChecks_Calculate_Corner_Positions_Test,
        Returns_correct_coordinates_for_aligned_rectangle)
    {
        Coll::RectComponent rectangleOne = Coll::RectComponent(0., 0., 100., 100.);
        Coll::RectComponent rectangleTwo = Coll::RectComponent(100., 100., 100., 100.);

        Coll::RectCorners cornersOne = Coll::calculateCornerPositions(
            rectangleOne.getRectangle()
        );
        Coll::RectCorners cornersTwo = Coll::calculateCornerPositions(
            rectangleTwo.getRectangle()
        );

        EXPECT_THAT(cornersOne.leftUpperXY, ::testing::ElementsAre(-50.f, -50.f));
        EXPECT_THAT(cornersOne.leftLowerXY, ::testing::ElementsAre(-50.f, 50.f));
        EXPECT_THAT(cornersOne.rightUpperXY, ::testing::ElementsAre(50.f, -50.f));
        EXPECT_THAT(cornersOne.rightLowerXY, ::testing::ElementsAre(50.f, 50.f));

        EXPECT_THAT(cornersTwo.leftUpperXY, ::testing::ElementsAre(50.f, 50.f));
        EXPECT_THAT(cornersTwo.leftLowerXY, ::testing::ElementsAre(50.f, 150.f));
        EXPECT_THAT(cornersTwo.rightUpperXY, ::testing::ElementsAre(150.f, 50.f));
        EXPECT_THAT(cornersTwo.rightLowerXY, ::testing::ElementsAre(150.f, 150.f));
    }

    TEST(CollisionChecks_Calculate_Corner_Positions_Test,
        Returns_correct_coordinates_for_unaligned_rectangle)
    {
        Coll::RectComponent rectangleOne = Coll::RectComponent(0., 0., 100., 100.);
        Coll::RectComponent rectangleTwo = Coll::RectComponent(100., 100., 100., 100.);
        rectangleOne.setAngle(270.f);
        rectangleTwo.setAngle(270.f);


        Coll::RectCorners cornersOne = Coll::calculateCornerPositions(
            rectangleOne.getRectangle()
        );
        Coll::RectCorners cornersTwo = Coll::calculateCornerPositions(
            rectangleTwo.getRectangle()
        );

        EXPECT_THAT(cornersOne.leftUpperXY, ::testing::ElementsAre(-50.f, 50.f));
        EXPECT_THAT(cornersOne.leftLowerXY, ::testing::ElementsAre(50.f, 50.f));
        EXPECT_THAT(cornersOne.rightUpperXY, ::testing::ElementsAre(-50.f, -50.f));
        EXPECT_THAT(cornersOne.rightLowerXY, ::testing::ElementsAre(50.f, -50.f));

        EXPECT_THAT(cornersTwo.leftUpperXY, ::testing::ElementsAre(50.f, 150.f));
        EXPECT_THAT(cornersTwo.leftLowerXY, ::testing::ElementsAre(150.f, 150.f));
        EXPECT_THAT(cornersTwo.rightUpperXY, ::testing::ElementsAre(50.f, 50.f));
        EXPECT_THAT(cornersTwo.rightLowerXY, ::testing::ElementsAre(150.f, 50.f));
    }

    TEST(CollisionChecks_Apply_Rotation_Matrix_Test,
        Returns_correct_corrdinates_for_positive_270_point_rotation)
    {
        std::array<float, 2> pointOne = {100.f, 100.f};
        float angleOne = 270.f;

        float matrixOne[2][2] = {
            {cos(angleOne * Coll::pi / 180.), -1.f * sin(angleOne * Coll::pi / 180.)},
            {cos(angleOne * Coll::pi / 180.), sin(angleOne * Coll::pi / 180.)}
        };

        std::array<float, 2> rotatedOne = Coll::applyRotationMatrix(pointOne, matrixOne);

        EXPECT_THAT(rotatedOne, ::testing::ElementsAre(100.f, -100.f));
    }

    TEST(CollisionChecks_Apply_Rotation_Matrix_Test,
        Returns_correct_corrdinates_for_negative_90_point_rotation)
    {
        std::array<float, 2> pointOne = { 100.f, 100.f };
        float angleOne = -90.f;

        float matrixOne[2][2] = {
            {cos(angleOne * Coll::pi / 180.), -1.f * sin(angleOne * Coll::pi / 180.)},
            {cos(angleOne * Coll::pi / 180.), sin(angleOne * Coll::pi / 180.)}
        };

        std::array<float, 2> rotatedOne = Coll::applyRotationMatrix(pointOne, matrixOne);

        EXPECT_THAT(rotatedOne, ::testing::ElementsAre(100.f, -100.f));
    }
}