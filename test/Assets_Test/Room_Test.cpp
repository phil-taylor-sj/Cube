#include "../pch.h"
#include "Assets/Room.h"
#include "Collision/Rectangle.h"

namespace Coll = Collision;

namespace Room_Tests
{
    TEST(Room_Constructor_Test,
        Initalises_eight_walls_at_correct_relative_position)
    {
        Room testRoom_1 = Room();
        testRoom_1.setCellWidth(100.f);
        testRoom_1.setCellIndices(0, 0);
        testRoom_1.updatePosition();
        const std::map<std::string, std::shared_ptr<StaticRectangle>>
            wallsMap = testRoom_1.getOuterWalls();

        Coll::RectParams wallLeft_1 = wallsMap.at("wallLeft1")->getRectangle();
        Coll::RectParams wallLeft_2 = wallsMap.at("wallLeft2")->getRectangle();
        Coll::RectParams wallRight_1 = wallsMap.at("wallRight1")->getRectangle();
        Coll::RectParams wallRight_2 = wallsMap.at("wallRight2")->getRectangle();
        Coll::RectParams wallUpper_1 = wallsMap.at("wallUpper1")->getRectangle();
        Coll::RectParams wallLower_1 = wallsMap.at("wallLower1")->getRectangle();
        Coll::RectParams wallUpper_2 = wallsMap.at("wallUpper2")->getRectangle();
        Coll::RectParams wallLower_2 = wallsMap.at("wallLower2")->getRectangle();

        EXPECT_EQ(wallLeft_1.x,  3.90625f);   EXPECT_EQ(wallLeft_1.y, 17.1875f);
        EXPECT_EQ(wallLeft_2.x,  3.90625f);   EXPECT_EQ(wallLeft_2.y, 82.8125f);
        EXPECT_EQ(wallRight_1.x, 96.09375f);  EXPECT_EQ(wallRight_1.y, 17.1875f);
        EXPECT_EQ(wallRight_2.x, 96.09375f);  EXPECT_EQ(wallRight_2.y, 82.8125f);

        EXPECT_EQ(wallUpper_1.x, 17.1875f);  EXPECT_EQ(wallUpper_1.y, 3.90625f);
        EXPECT_EQ(wallUpper_2.x, 82.8125f);  EXPECT_EQ(wallUpper_2.y, 3.90625f);
        EXPECT_EQ(wallLower_1.x, 17.1875f);  EXPECT_EQ(wallLower_1.y, 96.09375f);
        EXPECT_EQ(wallLower_2.x, 82.8125f);  EXPECT_EQ(wallLower_2.y, 96.09375f);
    }

    TEST(Room_Constructor_Test,
        Initialises_eight_walls_with_correct_dimensions)
    {
        Room testRoom_1 = Room();
        testRoom_1.setCellWidth(100.f);
        testRoom_1.setCellIndices(2, 2);
        testRoom_1.updatePosition();
        const std::map<std::string, std::shared_ptr<StaticRectangle>>
            wallsMap = testRoom_1.getOuterWalls();

        Coll::RectParams wallLeft_1 = wallsMap.at("wallLeft1")->getRectangle();
        Coll::RectParams wallLeft_2 = wallsMap.at("wallLeft2")->getRectangle();
        Coll::RectParams wallRight_1 = wallsMap.at("wallRight1")->getRectangle();
        Coll::RectParams wallRight_2 = wallsMap.at("wallRight2")->getRectangle();
        Coll::RectParams wallUpper_1 = wallsMap.at("wallUpper1")->getRectangle();
        Coll::RectParams wallLower_1 = wallsMap.at("wallLower1")->getRectangle();
        Coll::RectParams wallUpper_2 = wallsMap.at("wallUpper2")->getRectangle();
        Coll::RectParams wallLower_2 = wallsMap.at("wallLower2")->getRectangle();

        double tolerance = 1e-04;

        EXPECT_NEAR(wallLeft_1.width,   7.8125, tolerance);   
        EXPECT_NEAR(wallLeft_1.height,  34.375, tolerance);
        EXPECT_NEAR(wallLeft_2.width,   7.8125, tolerance);
        EXPECT_NEAR(wallLeft_2.height,  34.375, tolerance);
        EXPECT_NEAR(wallRight_1.width,  7.8125, tolerance);
        EXPECT_NEAR(wallRight_1.height, 34.375, tolerance);
        EXPECT_NEAR(wallRight_2.width,  7.8125, tolerance);
        EXPECT_NEAR(wallRight_2.height, 34.375, tolerance);
        EXPECT_NEAR(wallUpper_1.width,  34.375, tolerance);
        EXPECT_NEAR(wallUpper_1.height, 7.8125, tolerance);
        EXPECT_NEAR(wallUpper_2.width,  34.375, tolerance);
        EXPECT_NEAR(wallUpper_2.height, 7.8125, tolerance);
        EXPECT_NEAR(wallLower_1.width,  34.375, tolerance);
        EXPECT_NEAR(wallLower_1.height, 7.8125, tolerance);
        EXPECT_NEAR(wallLower_2.width,  34.375, tolerance);
        EXPECT_NEAR(wallLower_2.height, 7.8125, tolerance);
    }

    TEST(Room_Constructor_Test,
        Walls_move_with_the_node_position)
    {
        Room testRoom_1 = Room();
        testRoom_1.setCellWidth(100.f);
        testRoom_1.setCellIndices(10, 10);
        testRoom_1.updatePosition();
        const std::map<std::string, std::shared_ptr<StaticRectangle>>
            wallsMap = testRoom_1.getOuterWalls();

        Coll::RectParams wallLeft_1 = wallsMap.at("wallLeft1")->getRectangle();
        Coll::RectParams wallLeft_2 = wallsMap.at("wallLeft2")->getRectangle();
        Coll::RectParams wallRight_1 = wallsMap.at("wallRight1")->getRectangle();
        Coll::RectParams wallRight_2 = wallsMap.at("wallRight2")->getRectangle();
        Coll::RectParams wallUpper_1 = wallsMap.at("wallUpper1")->getRectangle();
        Coll::RectParams wallLower_1 = wallsMap.at("wallLower1")->getRectangle();
        Coll::RectParams wallUpper_2 = wallsMap.at("wallUpper2")->getRectangle();
        Coll::RectParams wallLower_2 = wallsMap.at("wallLower2")->getRectangle();

        double tolerance = 1e-01;

        EXPECT_NEAR(wallLeft_1.x, 1003.90625, tolerance);
        EXPECT_NEAR(wallLeft_1.y, 1017.1875, tolerance);
        EXPECT_NEAR(wallLeft_2.x, 1003.90625, tolerance);
        EXPECT_NEAR(wallLeft_2.y, 1082.8125, tolerance);
        EXPECT_NEAR(wallRight_1.x, 1096.09375, tolerance);
        EXPECT_NEAR(wallRight_1.y, 1017.1875, tolerance);
        EXPECT_NEAR(wallRight_2.x, 1096.09375, tolerance);
        EXPECT_NEAR(wallRight_2.y, 1082.8125, tolerance);
        EXPECT_NEAR(wallUpper_1.x, 1017.1875, tolerance);
        EXPECT_NEAR(wallUpper_1.y, 1003.90625, tolerance);
        EXPECT_NEAR(wallUpper_2.x, 1082.8125, tolerance);
        EXPECT_NEAR(wallUpper_2.y, 1003.90625, tolerance);
        EXPECT_NEAR(wallLower_1.x, 1017.1875, tolerance);
        EXPECT_NEAR(wallLower_1.y, 1096.09375, tolerance);
        EXPECT_NEAR(wallLower_2.x, 1082.8125, tolerance);
        EXPECT_NEAR(wallLower_2.y, 1096.09375, tolerance);
    }
}