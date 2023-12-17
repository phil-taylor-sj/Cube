cmake_minimum_required(VERSION 3.10)

enable_testing()

set(TEST_TARGET Cube_Tests)

include(Assets_Test/Assets_Test.cmake)
include(Collision_Test/Collision_Test.cmake)
include(Engine_Test/Engine_Test.cmake)
include(Utilities_Test/Utilities_Test.cmake)

set(TEST_SRCS
  pch.cpp
  pch.h
  ${ASSETS_TEST}
  ${COLLISION_TEST}
  ${ENGINE_TEST}
  ${UTILITIES_TEST}
  )

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(${TEST_TARGET} ${TEST_SRCS})
target_link_libraries(${TEST_TARGET} 
  gtest gtest_main gmock_main 
  Assets Collision Engine Obstacles States Utilities
  sfml-graphics sfml-window sfml-system)

target_include_directories(${TEST_TARGET} PUBLIC 
  ${PUBLIC_INCLUDE_DIR}
  ${SFML_INCLUDE_DIR}
  ) 

set_target_properties(${TEST_TARGET} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${BIN_DIR}
)

include(GoogleTest)
gtest_discover_tests(${TEST_TARGET})


