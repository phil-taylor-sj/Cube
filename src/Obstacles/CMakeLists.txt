cmake_minimum_required(VERSION 3.10)

add_library(Obstacles OBJECT
    StaticRectangle.cpp
)

target_include_directories(Obstacles PUBLIC 
    ${PUBLIC_INCLUDE_DIR}
    ${SFML_INCLUDE_DIR}
    )