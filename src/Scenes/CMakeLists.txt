cmake_minimum_required(VERSION 3.10)

add_library(Scenes OBJECT
    Scene.cpp
    GameScene.cpp
    TitleScene.cpp
 "SceneNames.h")

target_include_directories(Scenes PUBLIC 
    ${PUBLIC_INCLUDE_DIR}
    ${SFML_INCLUDE_DIR}
    )