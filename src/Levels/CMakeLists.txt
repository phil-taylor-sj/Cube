cmake_minimum_required(VERSION 3.10)

add_library(Levels OBJECT
    CellStaticWall.cpp
    LevelEntityManager.cpp
    LevelFactory.cpp
)

target_include_directories(Levels PUBLIC 
    ${PUBLIC_INCLUDE_DIR}
    ${SFML_INCLUDE_DIR}
    )