#include "../pch.h"
#include "Physics/CollisionChecks.h"

namespace phys = Physics;

namespace CollisionChecks_Tests
{

    class CollisionCirclesTestFixture : 
        public ::testing::TestWithParam<std::tuple<phys::Circle, phys::Circle>>
    {
    protected:
        void SetUp() override
        {
            this->circleOne = std::get<0>(GetParam());
            this->circleTwo = std::get<1>(GetParam());

        }
        phys::Circle circleOne, circleTwo;
    };

    class CollisionRectanglesTestFixture : 
        public ::testing::TestWithParam<std::tuple<phys::Rectangle, phys::Rectangle>>
    {
    protected:
        void SetUp() override
        {
            this->rectangleOne = std::get<0>(GetParam());
            this->rectangleTwo = std::get<1>(GetParam());

        }
        phys::Rectangle rectangleOne, rectangleTwo;
    };

    class CollisionUnalignedRectanglesTestFixture : 
        public ::testing::TestWithParam<std::tuple<phys::Rectangle, float, phys::Rectangle, float>>
    {
    protected:
        void SetUp() override
        {
            this->rectangleOne = std::get<0>(GetParam());
            this->angleOne = std::get<1>(GetParam());

            this->rectangleTwo = std::get<2>(GetParam());
            this->angleTwo = std::get<3>(GetParam());
        }
        phys::Rectangle rectangleOne, rectangleTwo;
        float angleOne, angleTwo;
    };

    class CollisionRectangleCircleTestFixture :
        public ::testing::TestWithParam<std::tuple<phys::Rectangle, float, phys::Circle>>
    {
    protected:
        void SetUp() override
        {
            this->rectangle = std::get<0>(GetParam());
            this->angle = std::get<1>(GetParam());
            this->circle = std::get<2>(GetParam());
        }
        phys::Circle circle;
        phys::Rectangle rectangle;
        float angle;
    };


    // --------------------------------------------------------------------------------------
    //            Testing collision detection between two circles
    // --------------------------------------------------------------------------------------

    class CollisionCirclesInteresctsFalse_F : public CollisionCirclesTestFixture {};
    TEST_P(CollisionCirclesInteresctsFalse_F, CollisionIntersectingCircles_ReturnsFalseTest)
    {
        EXPECT_FALSE(phys::checkIntersection(circleOne.getCircle(), circleTwo.getCircle()));
    }

    INSTANTIATE_TEST_SUITE_P(CollisionIntersectingCircles_ReturnsFalseTest, CollisionCirclesInteresctsFalse_F, ::testing::Values(
        // Circles  don't intersect.
        std::make_tuple<>(phys::Circle(225.5f, 300.f, 100.f), phys::Circle(425.f, 397.2f, 100.f)),
        std::make_tuple<>(phys::Circle(225.5f, 300.f, 100.f), phys::Circle(420.f, 350.f, 100.f)),
        std::make_tuple<>(phys::Circle(225.5f, 300.f, 100.f), phys::Circle(370.f, 360.f, 50.f)),
        std::make_tuple<>(phys::Circle(-225.5f, -300.f, 100.f), phys::Circle(-370.f, -360.f, 50.f))
    ));

    class CollisionCirclesInteresctsTrue_F : public CollisionCirclesTestFixture {};
    TEST_P(CollisionCirclesInteresctsTrue_F, CollisionIntersectingCircles_ReturnsTrueTest)
    {
        EXPECT_TRUE(phys::checkIntersection(circleOne.getCircle(), circleTwo.getCircle()));
    }

    INSTANTIATE_TEST_SUITE_P(CollisionIntersectingCircles_ReturnsTrueTest, CollisionCirclesInteresctsTrue_F, ::testing::Values(
        // Circles that intersect but don't share an origin.
        std::make_tuple<>(phys::Circle(225.5f, 300.f, 100.f), phys::Circle(415.f, 350.f, 100.f)),
        std::make_tuple<>(phys::Circle(225.5f, 300.f, 100.f), phys::Circle(365.f, 300.f, 50.f)),
        std::make_tuple<>(phys::Circle(-225.5f, -300.f, 100.f), phys::Circle(-365.f, -300.f, 50.)),
        // Circles that share an origin.
        std::make_tuple<>(phys::Circle(225.5f, 300.f, 100.f), phys::Circle(225.5f, 300.f, 100.f)),
        std::make_tuple<>(phys::Circle(225.5f, 300.f, 100.f), phys::Circle(225.5f, 300.f, 50.f)),
        std::make_tuple<>(phys::Circle(225.5f, -300.f, 100.f), phys::Circle(225.5f, -300.f, 50.f))
    ));

    // --------------------------------------------------------------------------------------
    //            Testing collision detection between two rectangles
    // --------------------------------------------------------------------------------------

    class CollisionAlignedRectanglesInteresctsFalse_F : public CollisionRectanglesTestFixture {};
    TEST_P(CollisionAlignedRectanglesInteresctsFalse_F, CollisionAlginedIntersectingRectangles_ReturnsFalseTest)
    {
        EXPECT_FALSE(phys::checkIntersection(rectangleOne.getRectangle(), rectangleTwo.getRectangle()));
        EXPECT_FALSE(phys::checkIntersection(rectangleTwo.getRectangle(), rectangleOne.getRectangle())); 
    }

    INSTANTIATE_TEST_SUITE_P(CollisionAlignedIntersectingRectangles_ReturnsFalseTest, 
        CollisionAlignedRectanglesInteresctsFalse_F, ::testing::Values(
        // Rectangles don't intersect.
        std::make_tuple<>(phys::Rectangle(350.f, 350.f, 300.f, 100.f), phys::Rectangle(350.f, 500.f, 400.f, 100.f)),
        std::make_tuple<>(phys::Rectangle(350.f, 350.f, 300.f, 100.f), phys::Rectangle(550.f, 450.f, 50.f, 50.f)),
        std::make_tuple<>(phys::Rectangle(350.f, 350.f, 300.f, 100.f), phys::Rectangle(550.f, 450.f, 100.f, 100.f)),
        std::make_tuple<>(phys::Rectangle(-350.f, -350.f, 300.f, 100.f), phys::Rectangle(-350.f, -500.f, 400.f, 100.f))
    ));

    class CollisionAlignedRectanglesInteresctsTrue_F : public CollisionRectanglesTestFixture {};
    TEST_P(CollisionAlignedRectanglesInteresctsTrue_F, CollisionAlignedIntersectingRectangles_ReturnsTrueTest)
    {
        EXPECT_TRUE(phys::checkIntersection(rectangleOne.getRectangle(), rectangleTwo.getRectangle()));
        EXPECT_TRUE(phys::checkIntersection(rectangleTwo.getRectangle(), rectangleOne.getRectangle()));
    }

    INSTANTIATE_TEST_SUITE_P(CollisionAlignedIntersecting_ReturnsTrueTest, CollisionAlignedRectanglesInteresctsTrue_F, ::testing::Values(
        // Two aligned rectangles which intersect returns true.
        std::make_tuple<>(phys::Rectangle(350.f, 350.f, 300.f, 100.f), phys::Rectangle(550.f, 450.f, 110.f, 110.f)),
        std::make_tuple<>(phys::Rectangle(350.f, 350.f, 300.f, 100.f), phys::Rectangle(350.f, 500.f, 400.f, 300.f)),
        std::make_tuple<>(phys::Rectangle(350.f, 350.f, 300.f, 100.f), phys::Rectangle(350.f, 500.f, 100.f, 300.f)),
        std::make_tuple<>(phys::Rectangle(350.f, 350.f, 300.f, 100.f), phys::Rectangle(350.f, 500.f, 100.f, 600.f)),
        std::make_tuple<>(phys::Rectangle(350.f, 350.f, 300.f, 100.f), phys::Rectangle(550.f, 450.f, 100.1f, 100.1f)),
        std::make_tuple<>(phys::Rectangle(350.f, 350.f, 300.f, 100.f), phys::Rectangle(550.f, 450.f, 2000.f, 2000.f)),
        std::make_tuple<>(phys::Rectangle(-350.f, -350.f, 300.f, 100.f), phys::Rectangle(-550.f, -450.f, 110.f, 110.f)),
        // One aligned rectangle centered within another aligned rectangle returns true.
        std::make_tuple<>(phys::Rectangle(350.f, 350.f, 300.f, 100.f), phys::Rectangle(350.f, 350.f, 310.f, 110.f)),
        std::make_tuple<>(phys::Rectangle(350.f, 350.f, 300.f, 100.f), phys::Rectangle(350.f, 350.f, 290.f, 90.f)),
        std::make_tuple<>(phys::Rectangle(350.f, 350.f, 300.f, 100.f), phys::Rectangle(300.f, 340.f, 50.f, 50.f)),
        std::make_tuple<>(phys::Rectangle(350.f, 350.f, 300.f, 100.f), phys::Rectangle(300.f, 340.f, 500.f, 200.f)),
        std::make_tuple<>(phys::Rectangle(-350.f, -350.f, 300.f, 100.f), phys::Rectangle(-300.f, -340.f, 400.f, 200.f))
    ));

    class CollisionUnalignedRectanglesInteresctsFalse_F : public CollisionUnalignedRectanglesTestFixture {};
    TEST_P(CollisionUnalignedRectanglesInteresctsFalse_F, CollisionUnalignedIntersectingRectangles_ReturnsFalseTest)
    {
        rectangleOne.setAngle(angleOne);
        rectangleTwo.setAngle(angleTwo);

        EXPECT_FALSE(phys::checkIntersection(rectangleOne.getRectangle(), rectangleTwo.getRectangle()));
        EXPECT_FALSE(phys::checkIntersection(rectangleTwo.getRectangle(), rectangleOne.getRectangle()));
    }

    INSTANTIATE_TEST_SUITE_P(CollisionUnalignedIntersectingRectangles_ReturnsFalseTest,
        CollisionUnalignedRectanglesInteresctsFalse_F, ::testing::Values(
            // One aligned rectangle and one unaligned rectangle which do not intersect.
            std::make_tuple<>(phys::Rectangle(750.f, 675.f, 500.f, 150.f), 20.f, phys::Rectangle(1100.f, 750.f, 100.f, 300.f), 0.f),
            std::make_tuple<>(phys::Rectangle(-750.f, -675.f, 500.f, 150.f), 20.f, phys::Rectangle(-1100.f, -750.f, 100.f, 300.f), 0.f),
            // Two unaligned rectangles which do not intersect.
            std::make_tuple<>(phys::Rectangle(750.f, 675.f, 500.f, 150.f), 350.f, phys::Rectangle(1100.f, 750.f, 100.f, 300.f), 70.f),
            std::make_tuple<>(phys::Rectangle(750.f, 675.f, 500.f, 150.f), 350.f, phys::Rectangle(900.f, 780.f, 100.f, 300.f), 80.f),
            std::make_tuple<>(phys::Rectangle(750.f, 675.f, 500.f, 150.f), 350.f, phys::Rectangle(-750.f, -675.f, 500.f, 150.f), 350.f),
            std::make_tuple<>(phys::Rectangle(750.f, 675.f, 500.f, 150.f), 350.f, phys::Rectangle(-1100.f, -750.f, 100.f, 300.f), 70.f)
        ));

    class CollisionUnalignedRectanglesInteresctsTrue_F : public CollisionUnalignedRectanglesTestFixture {};
    TEST_P(CollisionUnalignedRectanglesInteresctsTrue_F, CollisionUnalignedIntersectingRectangles_ReturnsTrueTest)
    {
        rectangleOne.setAngle(angleOne);
        rectangleTwo.setAngle(angleTwo);

        EXPECT_TRUE(phys::checkIntersection(rectangleOne.getRectangle(), rectangleTwo.getRectangle()));
        EXPECT_TRUE(phys::checkIntersection(rectangleTwo.getRectangle(), rectangleOne.getRectangle()));
    }

    INSTANTIATE_TEST_SUITE_P(CollisionUnalignedIntersectingRectangles_ReturnsFalseTest,
        CollisionUnalignedRectanglesInteresctsTrue_F, ::testing::Values(
            // One aligned rectangle and one unaligned rectangle which intersect.
            std::make_tuple<>(phys::Rectangle(750.f, 675.f, 500.f, 150.f), 0.f, phys::Rectangle(1100.f, 750.f, 100.f, 300.f), 70.f),
            std::make_tuple<>(phys::Rectangle(-750.f, -675.f, 500.f, 150.f), 0.f, phys::Rectangle(-1100.f, -750.f, 100.f, 300.f), 70.f),
            // Two unaligned rectangles which intersect.
            std::make_tuple<>(phys::Rectangle(750.f, 675.f, 500.f, 150.f), 20.f, phys::Rectangle(1100.f, 750.f, 100.f, 300.f), 70.f),
            std::make_tuple<>(phys::Rectangle(750.f, 675.f, 500.f, 150.f), 350.f, phys::Rectangle(900.f, 780.f, 100.f, 300.f), 170.f),
            std::make_tuple<>(phys::Rectangle(-750.f, -675.f, 500.f, 150.), 20.f, phys::Rectangle(-1100.f, -750.f, 100.f, 300.f), 70.f)
        ));

    // --------------------------------------------------------------------------------------
    //            Testing collision detection between a circle and a rectangle
    // --------------------------------------------------------------------------------------

    class CollisionAlignedRectangleCircleInteresctsFalse_F : public CollisionRectangleCircleTestFixture {};
    TEST_P(CollisionAlignedRectangleCircleInteresctsFalse_F, CollisionAlignedNotIntersectingRectangleCircle_ReturnsFalseTest)
    {
        EXPECT_FALSE(phys::checkIntersection(rectangle.getRectangle(), circle.getCircle()));
    }

    INSTANTIATE_TEST_SUITE_P(CollisionAlignedNotIntersectingRectangleCircle_ReturnsFalseTest,
        CollisionAlignedRectangleCircleInteresctsFalse_F, ::testing::Values(
            // Rectangle and circle don't intersect.
            std::make_tuple<>(phys::Rectangle(750.f, 675.f, 500.f, 150.f), 0.f, phys::Circle(850.f, 810.f, 50.f)),
            std::make_tuple<>(phys::Rectangle(750.f, 675.f, 500.f, 150.f), 0.f, phys::Circle(430.f, 670.f, 50.f)),
            std::make_tuple<>(phys::Rectangle(750.f, 675.f, 500.f, 150.f), 0.f, phys::Circle(450.f, 550.f, 50.f)),
            std::make_tuple<>(phys::Rectangle(750.f, 675.f, 500.f, 150.f), 0.f, phys::Circle(1050.f, 780.f, 50.f)),
            std::make_tuple<>(phys::Rectangle(-750.f, -675.f, 500.f, 150.f), 0.f, phys::Circle(-450.f, -550.f, 50.f)),
            std::make_tuple<>(phys::Rectangle(-750.f, -675.f, 500.f, 150.f), 0.f, phys::Circle(-1050.f, -780.f, 50.f))
        ));


    class CollisionAlignedRectangleCircleInteresctsTrue_F : public CollisionRectangleCircleTestFixture {};
    TEST_P(CollisionAlignedRectangleCircleInteresctsTrue_F, CollisionAlignedIntersectingRectangleCircle_ReturnsTrueTest)
    {
        EXPECT_TRUE(phys::checkIntersection(rectangle.getRectangle(), circle.getCircle()));
    }

    INSTANTIATE_TEST_SUITE_P(CollisionAlignedIntersectingRectangleCircle_ReturnsTrueTest,
        CollisionAlignedRectangleCircleInteresctsTrue_F, ::testing::Values(
            // Rectangle and circle intersect.
            std::make_tuple<>(phys::Rectangle(750.f, 675.f, 500.f, 150.f), 0.f, phys::Circle(850.f, 740.f, 50.f)),
            std::make_tuple<>(phys::Rectangle(750.f, 675.f, 500.f, 150.f), 0.f, phys::Circle(460.f, 670.f, 50.f)),
            std::make_tuple<>(phys::Rectangle(750.f, 675.f, 500.f, 150.f), 0.f, phys::Circle(480.f, 580.f, 50.f)),
            std::make_tuple<>(phys::Rectangle(750.f, 675.f, 500.f, 150.f), 0.f, phys::Circle(1030.f, 770.f, 50.f)),
            std::make_tuple<>(phys::Rectangle(750.f, 675.f, 500.f, 150.f), 0.f, phys::Circle(560.f, 670.f, 50.f)),
            std::make_tuple<>(phys::Rectangle(750.f, 675.f, 500.f, 150.f), 0.f, phys::Circle(750.f, 700.f, 50.f)),
            std::make_tuple<>(phys::Rectangle(-750.f, -675.f, 500.f, 150.f), 0.f, phys::Circle(-480.f, -580.f, 50.f)),
            std::make_tuple<>(phys::Rectangle(-750.f, -675.f, 500.f, 150.f), 0.f, phys::Circle(-1030.f, -770.f, 50.f))
        ));

    class CollisionUnalignedRectangleCircleInteresctsFalse_F : public CollisionRectangleCircleTestFixture {};
    TEST_P(CollisionUnalignedRectangleCircleInteresctsFalse_F, CollisionUnalignedNotIntersectingRectangleCircle_ReturnsFalseTest)
    {
        rectangle.setAngle(angle);
        EXPECT_FALSE(phys::checkIntersection(rectangle.getRectangle(), circle.getCircle()));
    }

    INSTANTIATE_TEST_SUITE_P(CollisionUnalignedNotIntersectingRectangleCircle_ReturnsFalseTest,
        CollisionUnalignedRectangleCircleInteresctsFalse_F, ::testing::Values(
            // Unaligned rectangle and circle that don't intersect.
            std::make_tuple<>(phys::Rectangle(750.f, 675.f, 500.f, 150.f), 30.f, phys::Circle(680.f, 810.f, 50.f)),
            std::make_tuple<>(phys::Rectangle(750.f, 675.f, 500.f, 150.f), 30.f, phys::Circle(480.f, 520.f, 50.f)),
            std::make_tuple<>(phys::Rectangle(750.f, 675.f, 500.f, 150.f), 30.f, phys::Circle(550.f, 430.f, 50.f)),
            std::make_tuple<>(phys::Rectangle(750.f, 675.f, 500.f, 150.f), 30.f, phys::Circle(940.f, 930.f, 50.f)),
            
            std::make_tuple<>(phys::Rectangle(-750.f, -675.f, 500.f, 150.f), 30.f, phys::Circle(-550.f, -430.f, 50.f)),
            std::make_tuple<>(phys::Rectangle(-750.f, -675.f, 500.f, 150.f), 30.f, phys::Circle(-940.f, -930.f, 50.f)),

            std::make_tuple<>(phys::Rectangle(750.f, 675.f, 500.f, 150.f), 310.f, phys::Circle(850.f, 770.f, 50.f)),
            std::make_tuple<>(phys::Rectangle(750.f, 675.f, 500.f, 150.f), 310.f, phys::Circle(530.f, 910.f, 50.f)),
            std::make_tuple<>(phys::Rectangle(750.f, 675.f, 500.f, 150.f), 310.f, phys::Circle(470.f, 830.f, 50.f)),
            std::make_tuple<>(phys::Rectangle(750.f, 675.f, 500.f, 150.f), 310.f, phys::Circle(1030.f, 530.f, 50.f)),
            
            std::make_tuple<>(phys::Rectangle(-750.f, -675.f, 500.f, 150.f), 310.f, phys::Circle(-470.f, -830.f, 50.f)),
            std::make_tuple<>(phys::Rectangle(-750.f, -675.f, 500.f, 150.f), 310.f, phys::Circle(-1030.f, -530.f, 50.f))
        ));

    class CollisionUnalignedRectangleCircleInteresctsTrue_F : public CollisionRectangleCircleTestFixture {};
    TEST_P(CollisionUnalignedRectangleCircleInteresctsTrue_F, CollisionUnalignedIntersectingRectangleCircle_ReturnsTrueTest)
    {
        rectangle.setAngle(angle);
        EXPECT_TRUE(phys::checkIntersection(rectangle.getRectangle(), circle.getCircle()));
    }

    INSTANTIATE_TEST_SUITE_P(CollisionUnalignedIntersectingRectangleCircle_ReturnsTrueTest,
        CollisionUnalignedRectangleCircleInteresctsFalse_F, ::testing::Values(
            // Unaligned rectangle and circle that intersect.
            std::make_tuple<>(phys::Rectangle(750.f, 675.f, 500.f, 150.f), 30.f, phys::Circle(690.f, 770.f, 50.f)),
            std::make_tuple<>(phys::Rectangle(750.f, 675.f, 500.f, 150.f), 30.f, phys::Circle(500.f, 530.f, 50.f)),
            std::make_tuple<>(phys::Rectangle(750.f, 675.f, 500.f, 150.f), 30.f, phys::Circle(570.f, 450.f, 50.f)),
            std::make_tuple<>(phys::Rectangle(750.f, 675.f, 500.f, 150.f), 30.f, phys::Circle(920.f, 900.f, 50.f)),
            std::make_tuple<>(phys::Rectangle(750.f, 675.f, 500.f, 150.f), 30.f, phys::Circle(610.f, 590.f, 50.f)),
            std::make_tuple<>(phys::Rectangle(750.f, 675.f, 500.f, 150.f), 30.f, phys::Circle(750.f, 700.f, 50.f)),
            
            std::make_tuple<>(phys::Rectangle(-750.f, -675.f, 500.f, 150.f), 30.f, phys::Circle(-570.f, -450.f, 50.f)),
            std::make_tuple<>(phys::Rectangle(-750.f, -675.f, 500.f, 150.f), 30.f, phys::Circle(-920.f, -900.f, 50.f)),

            std::make_tuple<>(phys::Rectangle(750.f, 675.f, 500.f, 150.f), 310.f, phys::Circle(830.f, 750.f, 50.f)),
            std::make_tuple<>(phys::Rectangle(750.f, 675.f, 500.f, 150.f), 310.f, phys::Circle(550.f, 890.f, 50.f)),
            std::make_tuple<>(phys::Rectangle(750.f, 675.f, 500.f, 150.f), 310.f, phys::Circle(490.f, 820.f, 50.f)),
            std::make_tuple<>(phys::Rectangle(750.f, 675.f, 500.f, 150.f), 310.f, phys::Circle(1010.f, 520.f, 50.f)),
            std::make_tuple<>(phys::Rectangle(750.f, 675.f, 500.f, 150.f), 310.f, phys::Circle(630.f, 810.f, 50.f)),
            std::make_tuple<>(phys::Rectangle(750.f, 675.f, 500.f, 150.f), 310.f, phys::Circle(750.f, 700.f, 50.f)),

            std::make_tuple<>(phys::Rectangle(-750.f, -675.f, 500.f, 150.f), 310.f, phys::Circle(-490.f, -820.f, 50.f)),
            std::make_tuple<>(phys::Rectangle(-750.f, -675.f, 500.f, 150.f), 310.f, phys::Circle(-1010.f, -520.f, 50.f))
        ));

    // --------------------------------------------------------------------------------------
    //            Testing calculation of corner positions for collision objects
    // --------------------------------------------------------------------------------------
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

    // --------------------------------------------------------------------------------------
    //            Testing rotation of collision objects by a rotation matrix
    // --------------------------------------------------------------------------------------

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