##
## EPITECH PROJECT, 2021
## Indie Studio
## File description:
## Bomberman game
##

cmake_minimum_required(VERSION 3.17)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(NAME bomberman)

project(${NAME} VERSION 0.1 LANGUAGES CXX)

## INCLUDES
include_directories(./include)

## SOURCES
set(SRCS
    ./src/main.cpp
)
add_executable(${NAME} ${SRCS})

## LIBS

# TODO link game engine lib
# TODO link raylibCpp lib