cmake_minimum_required(VERSION 3.10)

set(MAIN_SRC Cube.cpp)

# include(Assets/Assets.cmake)
# include(Collision/Collision.cmake)
# include(Engine/Engine.cmake)
# include(Obstacles/Obstacles.cmake)
# include(Utilities/Utilities.cmake)

# set(SRCS
#     ${ASSETS_SRCS} 
#     ${COLLISION_SRCS}
#     ${ENGINE_SRCS}
#     ${OBSTACLES_SRCS}
#     ${UTILITIES_SRCS}
# )

# add_library(Assets ${ASSETS_SRCS})
# add_library(Collision ${COLLISION_SRCS})
# add_library(Engine ${ENGINE_SRCS})
# add_library(Obstacles ${OBSTACLES_SRCS})
# add_library(Utilities ${UTILITIES_SRCS})

add_subdirectory(Assets)
add_subdirectory(Collision)
add_subdirectory(Engine)
add_subdirectory(Obstacles)
add_subdirectory(Utilities)

set(TARGET Cube)
add_executable(${TARGET} Cube.cpp)
target_link_libraries(${TARGET} PRIVATE 
    Assets Collision Engine Obstacles Utilities 
    sfml-graphics sfml-window sfml-system
    )

target_include_directories(${TARGET} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include) 

set_target_properties(${TARGET} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${BIN_DIR}
)

install(TARGETS ${TARGET} DESTINATION ${PROJECT_SOURCE_DIR}/bin)
