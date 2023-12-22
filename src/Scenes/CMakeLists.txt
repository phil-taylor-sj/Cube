cmake_minimum_required(VERSION 3.10)

add_library(States OBJECT
    BaseState.cpp
    GameMode.cpp
    Level.cpp
    TitleScreen.cpp
)

target_include_directories(States PUBLIC 
    ${PUBLIC_INCLUDE_DIR}
    ${SFML_INCLUDE_DIR}
    )