cmake_minimum_required(VERSION 3.10)

add_library(Engine OBJECT
    Action.cpp
    GameEngine.cpp
    Inputs.cpp
)


target_link_libraries(Engine VecPlus)

target_include_directories(Engine PUBLIC 
    ${PUBLIC_INCLUDE_DIR}
    ${SFML_INCLUDE_DIR}
    )