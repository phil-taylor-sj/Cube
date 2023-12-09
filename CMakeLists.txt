cmake_minimum_required(VERSION 3.10)

project(Cube)
enable_testing()

# Define C++ Version
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Define source
set(OBJ_DIR obj)
set(BIN_DIR bin)

set(BUILD_BIN_DIR ${PROJECT_SOURCE_DIR}/build/bin)
set(SFML_BIN_DIR ${PROJECT_SOURCE_DIR}/lib/SFML/bin)

set(SFML_DIR lib/SFML/lib/cmake/SFML)
find_package(SFML 2.6.1 COMPONENTS graphics window system REQUIRED)

execute_process(
	COMMAND ${CMAKE_COMMAND} -E make_directory ${BUILD_BIN_DIR}/Debug
	COMMAND ${CMAKE_COMMAND} -E copy ${SFML_BIN_DIR}/sfml-audio-d-2.dll ${BUILD_BIN_DIR}/Debug/
	COMMAND ${CMAKE_COMMAND} -E copy ${SFML_BIN_DIR}/sfml-graphics-d-2.dll ${BUILD_BIN_DIR}/Debug/
	COMMAND ${CMAKE_COMMAND} -E copy ${SFML_BIN_DIR}/sfml-system-d-2.dll ${BUILD_BIN_DIR}/Debug/
	COMMAND ${CMAKE_COMMAND} -E copy ${SFML_BIN_DIR}/sfml-network-d-2.dll ${BUILD_BIN_DIR}/Debug/
	COMMAND ${CMAKE_COMMAND} -E copy ${SFML_BIN_DIR}/sfml-window-d-2.dll ${BUILD_BIN_DIR}/Debug/
	COMMAND ${CMAKE_COMMAND} -E copy ${SFML_BIN_DIR}/openal32.dll ${BUILD_BIN_DIR}/Debug/
)

execute_process(
	COMMAND ${CMAKE_COMMAND} -E make_directory ${BUILD_BIN_DIR}/Release
	COMMAND ${CMAKE_COMMAND} -E copy ${SFML_BIN_DIR}/sfml-audio-2.dll ${BUILD_BIN_DIR}/Release/
	COMMAND ${CMAKE_COMMAND} -E copy ${SFML_BIN_DIR}/sfml-graphics-2.dll ${BUILD_BIN_DIR}/Release/
	COMMAND ${CMAKE_COMMAND} -E copy ${SFML_BIN_DIR}/sfml-system-2.dll ${BUILD_BIN_DIR}/Release/
	COMMAND ${CMAKE_COMMAND} -E copy ${SFML_BIN_DIR}/sfml-network-2.dll ${BUILD_BIN_DIR}/Release/
	COMMAND ${CMAKE_COMMAND} -E copy ${SFML_BIN_DIR}/sfml-window-2.dll ${BUILD_BIN_DIR}/Release/
	COMMAND ${CMAKE_COMMAND} -E copy ${SFML_BIN_DIR}/openal32.dll ${BUILD_BIN_DIR}/Release/
)

add_subdirectory(src)
add_subdirectory(test)