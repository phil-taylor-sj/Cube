cmake_minimum_required(VERSION 3.10)

add_library(Levels OBJECT
    DetectedLevelCollisions.cpp
    CellStaticRectangle.cpp
    LevelEntityManager.cpp
    LevelEntitySystem.cpp
    LevelMoveAction.cpp
    LevelFactory.cpp

 "DetectedLevelCollisions.cpp" "LevelMoveAction.cpp")

 
target_link_libraries(Levels VecPlus)

target_include_directories(Levels PUBLIC 
    ${PUBLIC_INCLUDE_DIR}
    ${SFML_INCLUDE_DIR}
    )