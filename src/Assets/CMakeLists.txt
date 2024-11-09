cmake_minimum_required(VERSION 3.10)

add_library(Assets OBJECT
    TextureDict.cpp
    FontDict.cpp
)

target_link_libraries(Assets VecPlus)


target_include_directories(Assets PUBLIC 
    ${PUBLIC_INCLUDE_DIR}
    ${SFML_INCLUDE_DIR}
    )