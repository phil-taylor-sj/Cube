cmake_minimum_required(VERSION 3.10)

add_library(Physics OBJECT
    Circle.cpp
    CollisionChecks.cpp
    Rectangle.cpp
    Vec2.cpp
 )

target_include_directories(Physics PUBLIC 
    ${PUBLIC_INCLUDE_DIR}
    )
    