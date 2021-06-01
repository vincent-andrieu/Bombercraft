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
    ./src/main.cpp
    ./src/EntityContainer/EntityRegister.cpp
    ./src/Component/Component.cpp
    ./src/system/PhysicsSystem/PhysicsSystem.cpp
    ./src/AbstractSystem/AbstractSystem.cpp
    ./src/EntityManager/EntityManager.cpp
    ./src/SystemManager/SystemManager.cpp
        )
#add_library(${NAME} SHARED ${SRCS})
add_executable(${NAME} ${SRCS}) # DEBUG

## LIB
# TODO : load cpp raylib
add_library(raylibcpp SHARED IMPORTED)
set_property(TARGET raylibcpp PROPERTY IMPORTED_LOCATION "${PROJECT_SOURCE_DIR}/../raylibCpp/libraylibcpp.so")
include_directories(${PROJECT_SOURCE_DIR}/../raylibCpp/include)
target_link_libraries(${NAME} raylibcpp)

