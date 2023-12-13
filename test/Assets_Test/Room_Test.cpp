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

        EXPECT_EQ(wallLeft_1.x, 3.90625f);
        EXPECT_EQ(wallLeft_1.y, 17.1875f);
    }
}