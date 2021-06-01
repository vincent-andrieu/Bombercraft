##
## EPITECH PROJECT, 2021
## Indie Studio
## File description:
## Bomberman game
##

cmake_minimum_required(VERSION 3.17)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(NAME bomberman)

project(${NAME} VERSION 0.1 LANGUAGES CXX)

## INCLUDES
include_directories(./include)

## SOURCES
set(SRCS
        ./src/main.cpp
        ./src/Game/ProceduralMap/ProceduralMap.cpp
        )
add_executable(${NAME} ${SRCS})

set_target_properties(${NAME}
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}"
        )

## LIBS

# TODO link game engine lib
# TODO link raylibCpp lib