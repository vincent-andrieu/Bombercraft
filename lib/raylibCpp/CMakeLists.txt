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
include_directories(./include)

## SOURCES
set(SRCS
    #./src/file.cpp
)
add_library(${NAME} SHARED ${SRCS})

## LIB
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "cmake")
find_package(raylib REQUIRED)
target_link_libraries(${NAME} raylib)
