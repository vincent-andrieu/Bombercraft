##
## EPITECH PROJECT, 2021
## Indie Studio
## File description:
## Bomberman game
##

cmake_minimum_required(VERSION 3.17)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(NAME cross)

project(${NAME} VERSION 0.1 LANGUAGES CXX)

## INCLUDES
include_directories(
    ./include
)

## SOURCES
set(SRCS
        src/Unistd.cpp
)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
add_library(${NAME} SHARED ${SRCS})

if(MSVC)
    target_compile_options(${NAME} PRIVATE /W4 /WX)
else()
    target_compile_options(${NAME} PRIVATE -Wall -Wextra)
endif()
