cmake_minimum_required(VERSION 3.10)

add_library(Assets OBJECT 
    "../../Legacy/Cell.cpp"
    Character.cpp
    Player.cpp
    "../../Legacy/Room.cpp"
    SpriteAsset.cpp
    "../../Legacy/Void.cpp"
    "../../Legacy/Walls.cpp"
)

target_include_directories(Assets PUBLIC 
    ${PUBLIC_INCLUDE_DIR}
    ${SFML_INCLUDE_DIR}
)