cmake_minimum_required(VERSION 3.10)

add_library(Scenes OBJECT
    Scene.cpp
    GameScene.cpp
    TitleScene.cpp
    GameOverScene.cpp
 "SceneNames.h")


target_link_libraries(Scenes VecPlus)

target_include_directories(Scenes PUBLIC 
    ${PUBLIC_INCLUDE_DIR}
    ${SFML_INCLUDE_DIR}
    )