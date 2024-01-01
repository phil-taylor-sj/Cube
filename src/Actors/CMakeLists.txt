cmake_minimum_required(VERSION 3.10)

add_library(Actors OBJECT 
    ActorEntityManager.cpp
    ActorEntitySystem.cpp
    ActorFactory.cpp
)

target_include_directories(Actors PUBLIC 
    ${PUBLIC_INCLUDE_DIR}
    ${SFML_INCLUDE_DIR}
)