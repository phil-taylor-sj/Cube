cmake_minimum_required(VERSION 3.10)

set(MAIN_SRC Cube.cpp)

include(Assets/Assets.cmake)
include(Collision/Collision.cmake)
include(Engine/Engine.cmake)
include(Utilities/Utilities.cmake)

set(SRCS 
    ${MAIN_SRC}
    ${ASSETS_SRCS} 
    ${COLLISION_SRCS}
    ${ENGINE_SRCS}
    ${UTILITIES_SRCS}
)

message(STATUS ${SRC_DIRS})

set(TARGET Cube)
add_executable(${TARGET} ${SRCS})
target_link_libraries(${TARGET} PRIVATE sfml-graphics sfml-window sfml-system)

set_target_properties(${TARGET} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${BIN_DIR}
)

install(TARGETS ${TARGET} DESTINATION ${PROJECT_SOURCE_DIR}/bin)
