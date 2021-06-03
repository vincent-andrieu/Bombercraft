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
include_directories(./src)

## SOURCES
set(SRCS
        ./src/main.cpp
        ./src/Game/Core/Core.cpp
        ./src/Game/ProceduralMap/ProceduralMap.cpp
        src/Components/Render3D/Render3D.cpp
        src/Components/Render2D/Render2D.cpp
        src/Systems/Render2D/Render2DSystem.cpp
        src/Systems/Render3D/Render3DSystem.cpp
        src/Scenes/DebugScene/DebugScene.cpp
        ./src/ConfigFile/ConfigFile.cpp
        ./src/Exceptions/Exceptions.cpp
        )
add_executable(${NAME} ${SRCS})

if (MSVC)
    target_compile_options(${NAME} PRIVATE /W4 /WX)
else ()
    target_compile_options(${NAME} PRIVATE -Wall) # -Wextra
endif ()

set_target_properties(${NAME}
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}"
        )

## GAME-ENGINE
add_subdirectory(${PROJECT_SOURCE_DIR}/lib/gameEngine/)
set(GAMEENGINE_DIR ${PROJECT_SOURCE_DIR}/lib/gameEngine)
include_directories(${GAMEENGINE_DIR}/include)
include_directories(${GAMEENGINE_DIR}/src)
target_link_libraries(${NAME} gameEngine)

## RAYLIB
add_subdirectory(${PROJECT_SOURCE_DIR}/lib/raylibCpp)
set(RAYLIB_DIR ${PROJECT_SOURCE_DIR}/lib/raylibCpp)
include_directories(${RAYLIB_DIR}/include)
target_link_libraries(${NAME} raylibcpp)
