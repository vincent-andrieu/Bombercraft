##
## EPITECH PROJECT, 2021
## Indie Studio
## File description:
## Bomberman game
##

cmake_minimum_required(VERSION 3.17)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(NAME gameEngine)

project(${NAME} VERSION 0.1 LANGUAGES CXX)

## INCLUDES
include_directories(
    ./include
    ./src/
)

## SOURCES
set(SRCS
    # Scenes
    src/SceneManager/SceneManager.cpp
    src/AbstractScene/AbstractScene.cpp
    # Systems
    src/SystemManager/SystemManager.cpp
    src/AbstractSystem/AbstractSystem.cpp
    src/Systems/PhysicsSystem/PhysicsSystem.cpp
    src/Systems/TimerSystem/TimerSystem.cpp
    # Factories
    src/EntityContainer/EntityRegister.cpp
    src/EntityManager/EntityManager.cpp
    # Components
    src/Component/Component.cpp
    src/components/Timer.cpp
    # Other
    src/EntityPack/EntityPack.cpp
    # Save
    #src/SaveManager/SaveManager.cpp
)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
add_library(${NAME} ${SRCS})

if(MSVC)
    target_compile_options(${NAME} PRIVATE /W4 /WX)
else()
    target_compile_options(${NAME} PRIVATE -Wall -Wextra)
endif()