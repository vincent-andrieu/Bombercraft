##
## EPITECH PROJECT, 2021
## Indie Studio
## File description:
## Bomberman game
##

cmake_minimum_required(VERSION 3.17)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(NAME raylibcpp)

project(${NAME} VERSION 0.1 LANGUAGES CXX)

## INCLUDES
include_directories(./include ./src)

## SOURCES
set(SRCS
    
    ./src/Audio/Music.cpp
    ./src/Audio/Sound.cpp
    ./src/Camera/Camera.cpp
    ./src/Data/Const.cpp
    ./src/File/Save.cpp
    ./src/Model/Animation.cpp
    ./src/Model/Model.cpp
    ./src/Shape/Rectangle.cpp
    ./src/Solid/Cuboid.cpp
    ./src/Text/Text.cpp
    ./src/Texture/Texture.cpp
    ./src/Window/Window.cpp
    ./src/Data/MyVector/MyVector2.cpp
    ./src/Data/MyVector/MyVector3.cpp
    ./src/Data/MyVector/MyVector4.cpp
    ./src/Input/Input.cpp
    ./src/Collision/Collision.cpp
    ./src/Collision/ObjectType/ObjectRectangle.cpp
    ./src/Collision/ObjectType/ObjectTriangle.cpp
    ./src/Collision/ObjectType/ObjectCircle.cpp
    ./src/Collision/ObjectType/ObjectSphere.cpp
    ./src/Collision/ObjectType/ObjectLine.cpp
    ./src/Collision/ObjectType/ObjectBox.cpp
)
add_library(${NAME} SHARED ${SRCS})

## LIB

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")
find_package(raylib REQUIRED)
target_link_libraries(${NAME} raylib)
