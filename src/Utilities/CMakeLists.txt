cmake_minimum_required(VERSION 3.10)

add_library(Utilities OBJECT
    GridGen.cpp
    VecMath.cpp
)

target_link_libraries(Utilities VecPlus)

target_include_directories(Utilities PUBLIC 
    ${PUBLIC_INCLUDE_DIR}
    ${SFML_INCLUDE_DIR}
    )