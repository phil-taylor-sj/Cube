cmake_minimum_required(VERSION 3.10)

add_library(Assets OBJECT 
    Cell.cpp
    Character.cpp
    Player.cpp
    Room.cpp
    SpriteAsset.cpp
    Void.cpp
    Walls.cpp
)

target_include_directories(Assets PUBLIC 
    ${PUBLIC_INCLUDE_DIR}
    ${SFML_INCLUDE_DIR}
)