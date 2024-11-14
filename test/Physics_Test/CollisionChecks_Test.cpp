#include "../pch.h"
#include "Physics/CollisionChecks.h"

namespace phys = Physics;

namespace CollisionChecks_Tests
{

    TEST(CollisionChecks_Intersects_Circles_Test,
        Two_circle_arguments_which_do_not_intersect_should_return_false)
    {
        phys::Circle circleBase = phys::Circle(225.5, 300., 100.);
        phys::Circle circleOne = phys::Circle(425., 397.2, 100.);
        phys::Circle circleTwo = phys::Circle(420., 350., 100.);
        phys::Circle circleThree = phys::Circle(370., 360., 50.);

        EXPECT_FALSE(phys::checkIntersection(circleBase.getCircle(), circleOne.getCircle()));
        EXPECT_FALSE(phys::checkIntersection(circleBase.getCircle(), circleTwo.getCircle()));
        EXPECT_FALSE(phys::checkIntersection(circleBase.getCircle(), circleThree.getCircle()));

        EXPECT_FALSE(
            phys::checkIntersection(
                phys::Circle(-225.5, -300., 100.).getCircle(),
                phys::Circle(-370., -360., 50.).getCircle()
            )
        );
    }

    TEST(CollisionChecks_Intersects_Circles_Test,
        Tcle_arguments_which_intersect_should_return_true
    )
    {
        phys::Circle circleBase = phys::Circle(225.5, 300., 100.);
        phys::Circle circleOne = phys::Circle(415., 350., 100.);
        phys::Circle circleTwo = phys::Circle(365., 300., 50.);

        EXPECT_TRUE(phys::checkIntersection(circleBase.getCircle(), circleOne.getCircle()));
        EXPECT_TRUE(phys::checkIntersection(circleBase.getCircle(), circleTwo.getCircle()));

        EXPECT_TRUE(
            phys::checkIntersection(
                phys::Circle(-225.5, -300., 100.).getCircle(),
                phys::Circle(-365., -300., 50.).getCircle()
            )
        );
    }

    TEST(CollisionChecks_Intersects_Circles_Test,
        Two_circle_arguments_sharing_an_origin_should_return_true
    )
    {
        phys::Circle circleBase = phys::Circle(225.5, 300., 100.);
        phys::Circle circleOne = phys::Circle(225.5, 300., 100.);
        phys::Circle circleTwo = phys::Circle(225.5, 300., 50.);

        EXPECT_TRUE(phys::checkIntersection(circleBase.getCircle(), circleOne.getCircle()));
        EXPECT_TRUE(phys::checkIntersection(circleBase.getCircle(), circleTwo.getCircle()));

        EXPECT_TRUE(
            phys::checkIntersection(
                phys::Circle(225.5, -300., 100.).getCircle(),
                phys::Circle(225.5, -300., 50.).getCircle()
            )
        );
    }

    TEST(CollisionChecks_Intersects_Rectangles_Test,
        Two_aligned_rectangle_arguments_which_do_not_intersect_should_return_false
    )
    {
        phys::Rectangle rectangleBase = phys::Rectangle(350., 350., 300., 100.);
        phys::Rectangle rectangleOne = phys::Rectangle(350., 500., 400., 100.);
        phys::Rectangle rectangleTwo = phys::Rectangle(550., 450., 50., 50.);
        phys::Rectangle rectangleThree = phys::Rectangle(550., 450., 100., 100.);

        EXPECT_FALSE(phys::checkIntersection(rectangleBase.getRectangle(), rectangleOne.getRectangle()));
        EXPECT_FALSE(phys::checkIntersection(rectangleOne.getRectangle(), rectangleBase.getRectangle()));

        EXPECT_FALSE(phys::checkIntersection(rectangleBase.getRectangle(), rectangleTwo.getRectangle()));
        EXPECT_FALSE(phys::checkIntersection(rectangleTwo.getRectangle(), rectangleBase.getRectangle()));

        EXPECT_FALSE(phys::checkIntersection(rectangleBase.getRectangle(), rectangleThree.getRectangle()));
        EXPECT_FALSE(phys::checkIntersection(rectangleThree.getRectangle(), rectangleBase.getRectangle()));

        EXPECT_FALSE(
            phys::checkIntersection(
                phys::Rectangle(-350., -350., 300., 100.).getRectangle(),
                phys::Rectangle(-350., -500., 400., 100.).getRectangle()
            )
        );
    }

    TEST(CollisionChecks_Intersects_Rectangles_Test,
        Two_aligned_rectangle_arguments_which_intersect_should_return_true
    )
    {
        phys::Rectangle rectangleBase = phys::Rectangle(350., 350., 300., 100.);
        phys::Rectangle rectangleOne = phys::Rectangle(550., 450., 110., 110.);
        phys::Rectangle rectangleTwo = phys::Rectangle(350., 500., 400., 300.);
        phys::Rectangle rectangleThree = phys::Rectangle(350., 500., 100., 300.);
        phys::Rectangle rectangleFour = phys::Rectangle(350., 500., 100., 600.);
        phys::Rectangle rectangleFive = phys::Rectangle(550., 450., 100.1, 100.1);
        phys::Rectangle rectangleSix = phys::Rectangle(550., 450., 2000., 2000.);

        EXPECT_TRUE(phys::checkIntersection(rectangleBase.getRectangle(), rectangleOne.getRectangle()));
        EXPECT_TRUE(phys::checkIntersection(rectangleOne.getRectangle(), rectangleBase.getRectangle()));

        EXPECT_TRUE(phys::checkIntersection(rectangleBase.getRectangle(), rectangleTwo.getRectangle()));
        EXPECT_TRUE(phys::checkIntersection(rectangleTwo.getRectangle(), rectangleBase.getRectangle()));

        EXPECT_TRUE(phys::checkIntersection(rectangleBase.getRectangle(), rectangleThree.getRectangle()));
        EXPECT_TRUE(phys::checkIntersection(rectangleThree.getRectangle(), rectangleBase.getRectangle()));

        EXPECT_TRUE(phys::checkIntersection(rectangleBase.getRectangle(), rectangleFour.getRectangle()));
        EXPECT_TRUE(phys::checkIntersection(rectangleFour.getRectangle(), rectangleBase.getRectangle()));

        EXPECT_TRUE(phys::checkIntersection(rectangleBase.getRectangle(), rectangleFive.getRectangle()));
        EXPECT_TRUE(phys::checkIntersection(rectangleFive.getRectangle(), rectangleBase.getRectangle()));

        EXPECT_TRUE(phys::checkIntersection(rectangleBase.getRectangle(), rectangleSix.getRectangle()));
        EXPECT_TRUE(phys::checkIntersection(rectangleSix.getRectangle(), rectangleBase.getRectangle()));

        EXPECT_TRUE(
            phys::checkIntersection(
                phys::Rectangle(-350., -350., 300., 100.).getRectangle(),
                phys::Rectangle(-550., -450., 110., 110.).getRectangle()
            )
        );
    }

    TEST(CollisionChecks_Intersects_Rectangles_Test,
        One_aligned_rectangle_centred_within_another_aligned_rectangle_returns_true
    )
    {
        phys::Rectangle rectangleBase = phys::Rectangle(350., 350., 300., 100.);
        phys::Rectangle rectangleOne = phys::Rectangle(350., 350., 310., 110.);
        phys::Rectangle rectangleTwo = phys::Rectangle(350., 350., 290., 90.);
        phys::Rectangle rectangleThree = phys::Rectangle(300., 340., 50., 50.);
        phys::Rectangle rectangleFour = phys::Rectangle(300., 340., 500., 200.);

        EXPECT_TRUE(phys::checkIntersection(rectangleBase.getRectangle(), rectangleOne.getRectangle()));
        EXPECT_TRUE(phys::checkIntersection(rectangleBase.getRectangle(), rectangleTwo.getRectangle()));

        EXPECT_TRUE(phys::checkIntersection(rectangleBase.getRectangle(), rectangleThree.getRectangle()));
        EXPECT_TRUE(phys::checkIntersection(rectangleThree.getRectangle(), rectangleBase.getRectangle()));

        EXPECT_TRUE(phys::checkIntersection(rectangleBase.getRectangle(), rectangleFour.getRectangle()));
        EXPECT_TRUE(phys::checkIntersection(rectangleFour.getRectangle(), rectangleBase.getRectangle()));

        EXPECT_TRUE(
            phys::checkIntersection(
                phys::Rectangle(-350., -350., 300., 100.).getRectangle(),
                phys::Rectangle(-300., -340., 400., 200.).getRectangle()
            )
        );
    }

    TEST(CollisionChecks_Intersects_Rectangles_Test,
        One_aligned_and_one_unaligned_rectangle_which_do_not_intersect_returns_false
    )
    {
        phys::Rectangle rectangleBase = phys::Rectangle(750., 675., 500., 150.);
        phys::Rectangle rectangleOne = phys::Rectangle(1100., 750., 100., 300.);

        phys::Rectangle rectangleTwo = phys::Rectangle(-750., -675., 500., 150.);
        phys::Rectangle rectangleThree = phys::Rectangle(-1100., -750., 100., 300.);

        rectangleBase.setAngle(20);
        rectangleTwo.setAngle(20);

        EXPECT_FALSE(phys::checkIntersection(rectangleBase.getRectangle(), rectangleOne.getRectangle()));
        EXPECT_FALSE(phys::checkIntersection(rectangleOne.getRectangle(), rectangleBase.getRectangle()));

        EXPECT_FALSE(phys::checkIntersection(rectangleTwo.getRectangle(), rectangleThree.getRectangle()));
        EXPECT_FALSE(phys::checkIntersection(rectangleThree.getRectangle(), rectangleTwo.getRectangle()));
    }

    TEST(CollisionChecks_Intersects_Rectangles_Test,
        One_aligned_and_one_unaligned_rectangle_which_intersect_returns_true
    )
    {
        phys::Rectangle rectangleBase = phys::Rectangle(750., 675., 500., 150.);
        phys::Rectangle rectangleOne = phys::Rectangle(1100., 750., 100., 300.);

        phys::Rectangle rectangleTwo = phys::Rectangle(-750., -675., 500., 150.);
        phys::Rectangle rectangleThree = phys::Rectangle(-1100., -750., 100., 300.);

        rectangleOne.setAngle(70.);
        rectangleThree.setAngle(70.);

        EXPECT_TRUE(phys::checkIntersection(rectangleBase.getRectangle(), rectangleOne.getRectangle()));
        EXPECT_TRUE(phys::checkIntersection(rectangleOne.getRectangle(), rectangleBase.getRectangle()));

        EXPECT_TRUE(phys::checkIntersection(rectangleTwo.getRectangle(), rectangleThree.getRectangle()));
        EXPECT_TRUE(phys::checkIntersection(rectangleThree.getRectangle(), rectangleTwo.getRectangle()));
    }

    TEST(CollisionChecks_Intersects_Rectangles_Test,
        Two_unaligned_rectangles_which_do_not_intersect_returns_false
    )
    {
        phys::Rectangle rectangleBase = phys::Rectangle(750., 675., 500., 150.);
        phys::Rectangle rectangleOne = phys::Rectangle(1100., 750., 100., 300.);
        phys::Rectangle rectangleTwo = phys::Rectangle(900., 780., 100., 300.);

        phys::Rectangle rectangleThree = phys::Rectangle(-750., -675., 500., 150.);
        phys::Rectangle rectangleFour = phys::Rectangle(-1100., -750., 100., 300.);

        rectangleBase.setAngle(350.);
        rectangleOne.setAngle(70.);
        rectangleTwo.setAngle(80.);
        rectangleThree.setAngle(350.);
        rectangleFour.setAngle(70.);

        EXPECT_FALSE(phys::checkIntersection(rectangleBase.getRectangle(), rectangleOne.getRectangle()));
        EXPECT_FALSE(phys::checkIntersection(rectangleOne.getRectangle(), rectangleBase.getRectangle()));

        EXPECT_FALSE(phys::checkIntersection(rectangleBase.getRectangle(), rectangleTwo.getRectangle()));
        EXPECT_FALSE(phys::checkIntersection(rectangleTwo.getRectangle(), rectangleBase.getRectangle()));

        EXPECT_FALSE(phys::checkIntersection(rectangleThree.getRectangle(), rectangleFour.getRectangle()));
        EXPECT_FALSE(phys::checkIntersection(rectangleFour.getRectangle(), rectangleThree.getRectangle()));
    }

    TEST(CollisionChecks_Intersects_Rectangles_Test,
        Two_unaligned_rectangles_which_intersect_returns_true
    )
    {
        phys::Rectangle rectangleBase = phys::Rectangle(750., 675., 500., 150.);
        phys::Rectangle rectangleOne = phys::Rectangle(1100., 750., 100., 300.);
        phys::Rectangle rectangleTwo = phys::Rectangle(900., 780., 100., 300.);

        phys::Rectangle rectangleThree = phys::Rectangle(-750., -675., 500., 150.);
        phys::Rectangle rectangleFour = phys::Rectangle(-1100., -750., 100., 300.);

        rectangleBase.setAngle(20.);
        rectangleOne.setAngle(70.);
        rectangleTwo.setAngle(170.);

        rectangleThree.setAngle(20.);
        rectangleFour.setAngle(70.);

        EXPECT_TRUE(phys::checkIntersection(rectangleBase.getRectangle(), rectangleOne.getRectangle()));
        EXPECT_TRUE(phys::checkIntersection(rectangleOne.getRectangle(), rectangleBase.getRectangle()));

        rectangleBase.setAngle(350.);
        EXPECT_TRUE(phys::checkIntersection(rectangleBase.getRectangle(), rectangleTwo.getRectangle()));
        EXPECT_TRUE(phys::checkIntersection(rectangleTwo.getRectangle(), rectangleBase.getRectangle()));

        EXPECT_TRUE(phys::checkIntersection(rectangleThree.getRectangle(), rectangleFour.getRectangle()));
        EXPECT_TRUE(phys::checkIntersection(rectangleFour.getRectangle(), rectangleThree.getRectangle()));
    }

    TEST(CollisionChecks_Intersects_Rectangle_Circle_Test,
        An_aligned_rectangle_and_a_circle_which_do_not_intersect_returns_false
    )
    {
        phys::Rectangle rectangleBase = phys::Rectangle(750.f, 675.f, 500.f, 150.f);
        phys::Circle circleOne = phys::Circle(850.f, 810.f, 50.f);
        phys::Circle circleTwo = phys::Circle(430.f, 670.f, 50.f);
        phys::Circle circleThree = phys::Circle(450.f, 550.f, 50.f);
        phys::Circle circleFour = phys::Circle(1050.f, 780.f, 50.f);

        EXPECT_FALSE(phys::checkIntersection(rectangleBase.getRectangle(), circleOne.getCircle()));
        EXPECT_FALSE(phys::checkIntersection(rectangleBase.getRectangle(), circleTwo.getCircle()));
        EXPECT_FALSE(phys::checkIntersection(rectangleBase.getRectangle(), circleThree.getCircle()));
        EXPECT_FALSE(phys::checkIntersection(rectangleBase.getRectangle(), circleFour.getCircle()));

        phys::Rectangle rectangleOne = phys::Rectangle(-750.f, -675.f, 500.f, 150.f);
        phys::Circle circleFive = phys::Circle(-450.f, -550.f, 50.f);
        phys::Circle circleSix = phys::Circle(-1050.f, -780.f, 50.f);

        EXPECT_FALSE(phys::checkIntersection(rectangleOne.getRectangle(), circleFive.getCircle()));
        EXPECT_FALSE(phys::checkIntersection(rectangleOne.getRectangle(), circleSix.getCircle()));
    }

    TEST(CollisionChecks_Intersects_Rectangle_Circle_Test,
        An_aligned_rectangle_and_a_circle_which_intersect_returns_true
    )
    {
        phys::Rectangle rectangleBase = phys::Rectangle(750.f, 675.f, 500.f, 150.f);
        phys::Circle circleOne = phys::Circle(850.f, 740.f, 50.f);
        phys::Circle circleTwo = phys::Circle(460.f, 670.f, 50.f);
        phys::Circle circleThree = phys::Circle(480.f, 580.f, 50.f);
        phys::Circle circleFour = phys::Circle(1030.f, 770.f, 50.f);
        phys::Circle circleFive = phys::Circle(560.f, 670.f, 50.f);
        phys::Circle circleSix = phys::Circle(750.f, 700.f, 50.f);

        EXPECT_TRUE(phys::checkIntersection(rectangleBase.getRectangle(), circleOne.getCircle()));
        EXPECT_TRUE(phys::checkIntersection(rectangleBase.getRectangle(), circleTwo.getCircle()));
        EXPECT_TRUE(phys::checkIntersection(rectangleBase.getRectangle(), circleThree.getCircle()));
        EXPECT_TRUE(phys::checkIntersection(rectangleBase.getRectangle(), circleFour.getCircle()));
        EXPECT_TRUE(phys::checkIntersection(rectangleBase.getRectangle(), circleFive.getCircle()));
        EXPECT_TRUE(phys::checkIntersection(rectangleBase.getRectangle(), circleSix.getCircle()));

        phys::Rectangle rectangleOne = phys::Rectangle(-750.f, -675.f, 500.f, 150.f);
        phys::Circle circleSeven = phys::Circle(-480.f, -580.f, 50.f);
        phys::Circle circleEight = phys::Circle(-1030.f, -770.f, 50.f);

        EXPECT_TRUE(phys::checkIntersection(rectangleOne.getRectangle(), circleSeven.getCircle()));
        EXPECT_TRUE(phys::checkIntersection(rectangleOne.getRectangle(), circleEight.getCircle()));



    }

    TEST(CollisionChecks_Intersects_Rectangle_Circle_Test,
        An_unaligned_rectangle_and_a_circle_which_do_not_intersect_returns_false
    )
    {
        phys::Rectangle rectangleBase = phys::Rectangle(750.f, 675.f, 500.f, 150.f);
        rectangleBase.setAngle(30.f);

        phys::Circle circleOne = phys::Circle(680.f, 810.f, 50.f);
        phys::Circle circleTwo = phys::Circle(480.f, 520.f, 50.f);
        phys::Circle circleThree = phys::Circle(550.f, 430.f, 50.f);
        phys::Circle circleFour = phys::Circle(940.f, 930.f, 50.f);

        EXPECT_FALSE(phys::checkIntersection(rectangleBase.getRectangle(), circleOne.getCircle()));
        EXPECT_FALSE(phys::checkIntersection(rectangleBase.getRectangle(), circleTwo.getCircle()));
        EXPECT_FALSE(phys::checkIntersection(rectangleBase.getRectangle(), circleThree.getCircle()));
        EXPECT_FALSE(phys::checkIntersection(rectangleBase.getRectangle(), circleFour.getCircle()));


        phys::Rectangle rectangleOne = phys::Rectangle(-750.f, -675.f, 500.f, 150.f);
        rectangleOne.setAngle(30.f);
        phys::Circle circleFive = phys::Circle(-550.f, -430.f, 50.f);
        phys::Circle circleSix = phys::Circle(-940.f, -930.f, 50.f);

        EXPECT_FALSE(phys::checkIntersection(rectangleOne.getRectangle(), circleFive.getCircle()));
        EXPECT_FALSE(phys::checkIntersection(rectangleOne.getRectangle(), circleSix.getCircle()));

    }

    TEST(CollisionChecks_Intersects_Rectangle_Circle_Test,
        An_unaligned_rectangle_and_a_circle_which_intersect_returns_true
    )
    {
        phys::Rectangle rectangleBase = phys::Rectangle(750.f, 675.f, 500.f, 150.f);
        rectangleBase.setAngle(30.f);

        phys::Circle circleOne = phys::Circle(690.f, 770.f, 50.f);
        phys::Circle circleTwo = phys::Circle(500.f, 530.f, 50.f);
        phys::Circle circleThree = phys::Circle(570.f, 450.f, 50.f);
        phys::Circle circleFour = phys::Circle(920.f, 900.f, 50.f);
        phys::Circle circleFive = phys::Circle(610.f, 590.f, 50.f);
        phys::Circle circleSix = phys::Circle(750.f, 700.f, 50.f);

        EXPECT_TRUE(phys::checkIntersection(rectangleBase.getRectangle(), circleOne.getCircle()));
        EXPECT_TRUE(phys::checkIntersection(rectangleBase.getRectangle(), circleTwo.getCircle()));
        EXPECT_TRUE(phys::checkIntersection(rectangleBase.getRectangle(), circleThree.getCircle()));
        EXPECT_TRUE(phys::checkIntersection(rectangleBase.getRectangle(), circleFour.getCircle()));
        EXPECT_TRUE(phys::checkIntersection(rectangleBase.getRectangle(), circleFive.getCircle()));
        EXPECT_TRUE(phys::checkIntersection(rectangleBase.getRectangle(), circleSix.getCircle()));

        phys::Rectangle rectangleOne = phys::Rectangle(-750.f, -675.f, 500.f, 150.f);
        rectangleOne.setAngle(30.f);
        phys::Circle circleSeven = phys::Circle(-570.f, -450.f, 50.f);
        phys::Circle circleEight = phys::Circle(-920.f, -900.f, 50.f);

        EXPECT_TRUE(phys::checkIntersection(rectangleOne.getRectangle(), circleSeven.getCircle()));
        EXPECT_TRUE(phys::checkIntersection(rectangleOne.getRectangle(), circleEight.getCircle()));

    }

    TEST(CollisionChecks_Intersects_Rectangle_Circle_Test,
        An_unaligned_310_rectangle_and_a_circle_which_do_not_intersect_returns_false
    )
    {
        phys::Rectangle rectangleBase = phys::Rectangle(750.f, 675.f, 500.f, 150.f);
        rectangleBase.setAngle(310.f);

        phys::Circle circleOne = phys::Circle(850.f, 770.f, 50.f);
        phys::Circle circleTwo = phys::Circle(530.f, 910.f, 50.f);
        phys::Circle circleThree = phys::Circle(470.f, 830.f, 50.f);
        phys::Circle circleFour = phys::Circle(1030.f, 530.f, 50.f);

        EXPECT_FALSE(phys::checkIntersection(rectangleBase.getRectangle(), circleOne.getCircle()));
        EXPECT_FALSE(phys::checkIntersection(rectangleBase.getRectangle(), circleTwo.getCircle()));
        EXPECT_FALSE(phys::checkIntersection(rectangleBase.getRectangle(), circleThree.getCircle()));
        EXPECT_FALSE(phys::checkIntersection(rectangleBase.getRectangle(), circleFour.getCircle()));


        phys::Rectangle rectangleOne = phys::Rectangle(-750.f, -675.f, 500.f, 150.f);
        rectangleOne.setAngle(310.f);
        phys::Circle circleFive = phys::Circle(-470.f, -830.f, 50.f);
        phys::Circle circleSix = phys::Circle(-1030.f, -530.f, 50.f);

        EXPECT_FALSE(phys::checkIntersection(rectangleOne.getRectangle(), circleFive.getCircle()));
        EXPECT_FALSE(phys::checkIntersection(rectangleOne.getRectangle(), circleSix.getCircle()));
    }

    TEST(CollisionChecks_Intersects_Rectangle_Circle_Test,
        An_unaligned_310_rectangle_and_a_circle_which_intersect_returns_true
    )
    {
        phys::Rectangle rectangleBase = phys::Rectangle(750.f, 675.f, 500.f, 150.f);
        rectangleBase.setAngle(310.f);

        phys::Circle circleOne = phys::Circle(830.f, 750.f, 50.f);
        phys::Circle circleTwo = phys::Circle(550.f, 890.f, 50.f);
        phys::Circle circleThree = phys::Circle(490.f, 820.f, 50.f);
        phys::Circle circleFour = phys::Circle(1010.f, 520.f, 50.f);
        phys::Circle circleFive = phys::Circle(630.f, 810.f, 50.f);
        phys::Circle circleSix = phys::Circle(750.f, 700.f, 50.f);

        EXPECT_TRUE(phys::checkIntersection(rectangleBase.getRectangle(), circleOne.getCircle()));
        EXPECT_TRUE(phys::checkIntersection(rectangleBase.getRectangle(), circleTwo.getCircle()));
        EXPECT_TRUE(phys::checkIntersection(rectangleBase.getRectangle(), circleThree.getCircle()));
        EXPECT_TRUE(phys::checkIntersection(rectangleBase.getRectangle(), circleFour.getCircle()));
        EXPECT_TRUE(phys::checkIntersection(rectangleBase.getRectangle(), circleFive.getCircle()));
        EXPECT_TRUE(phys::checkIntersection(rectangleBase.getRectangle(), circleSix.getCircle()));

        phys::Rectangle rectangleOne = phys::Rectangle(-750.f, -675.f, 500.f, 150.f);
        rectangleOne.setAngle(310.f);
        phys::Circle circleSeven = phys::Circle(-490.f, -820.f, 50.f);
        phys::Circle circleEight = phys::Circle(-1010.f, -520.f, 50.f);

        EXPECT_TRUE(phys::checkIntersection(rectangleOne.getRectangle(), circleSeven.getCircle()));
        EXPECT_TRUE(phys::checkIntersection(rectangleOne.getRectangle(), circleEight.getCircle()));
    }

    TEST(CollisionChecks_Calculate_Corner_Positions_Test,
        Returns_correct_coordinates_for_aligned_rectangle)
    {
        phys::Rectangle rectangleOne = phys::Rectangle(0., 0., 100., 100.);
        phys::Rectangle rectangleTwo = phys::Rectangle(100., 100., 100., 100.);

        phys::RectCorners cornersOne = phys::calculateCornerPositions(
            rectangleOne.getRectangle()
        );
        phys::RectCorners cornersTwo = phys::calculateCornerPositions(
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
        phys::Rectangle rectangleOne = phys::Rectangle(0., 0., 100., 100.);
        phys::Rectangle rectangleTwo = phys::Rectangle(100., 100., 100., 100.);
        rectangleOne.setAngle(270.f);
        rectangleTwo.setAngle(270.f);


        phys::RectCorners cornersOne = phys::calculateCornerPositions(
            rectangleOne.getRectangle()
        );
        phys::RectCorners cornersTwo = phys::calculateCornerPositions(
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
        std::array<float, 2> pointOne = { 100.f, 100.f };
        float angleOne = 270.f;

        float matrixOne[2][2] = {
            {cos(angleOne * phys::pi / 180.), -1.f * sin(angleOne * phys::pi / 180.)},
            {cos(angleOne * phys::pi / 180.), sin(angleOne * phys::pi / 180.)}
        };

        std::array<float, 2> rotatedOne = phys::applyRotationMatrix(pointOne, matrixOne);

        EXPECT_THAT(rotatedOne, ::testing::ElementsAre(100.f, -100.f));
    }

    TEST(CollisionChecks_Apply_Rotation_Matrix_Test,
        Returns_correct_corrdinates_for_negative_90_point_rotation)
    {
        std::array<float, 2> pointOne = { 100.f, 100.f };
        float angleOne = -90.f;

        float matrixOne[2][2] = {
            {cos(angleOne * phys::pi / 180.), -1.f * sin(angleOne * phys::pi / 180.)},
            {cos(angleOne * phys::pi / 180.), sin(angleOne * phys::pi / 180.)}
        };

        std::array<float, 2> rotatedOne = phys::applyRotationMatrix(pointOne, matrixOne);

        EXPECT_THAT(rotatedOne, ::testing::ElementsAre(100.f, -100.f));
    }
}