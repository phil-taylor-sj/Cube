cmake_minimum_required(VERSION 3.10)

add_library(Collision OBJECT
    Circle.cpp
    CollisionChecks.cpp
    Rectangle.cpp
)

target_include_directories(Collision PUBLIC 
    ${PUBLIC_INCLUDE_DIR}
    ${SFML_INCLUDE_DIR}
    )
    