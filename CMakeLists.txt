##
## EPITECH PROJECT, 2021
## Indie Studio
## File description:
## Bomberman game
##

cmake_minimum_required(VERSION 3.17)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(NAME bomberman)

project(${NAME} VERSION 0.1 LANGUAGES CXX)

## INCLUDES
include_directories(./include)
include_directories(./src)

## SOURCES
set(SRCS
        src/main.cpp
        # GAME
        src/Game/Core/Core.cpp
        src/Game/CoreData/CoreData.cpp
        src/Game/ProceduralMap/ProceduralMap.cpp
        src/Game/EventRequirement/EventRequirement.cpp
        src/ConfigFile/ConfigFile.cpp
        src/Exceptions/Exceptions.cpp
        ## GAME/FACTORIES
        src/Game/Factories/Block/BlockFactory.cpp
        src/Game/Factories/Sound/AudioFactory.cpp
        ## TMP
        src/Game/Factories/Map/Component/DataMatrix/DataMatrix.cpp
        src/Game/Factories/Map/Component/Matrix2D.cpp
        src/Game/Factories/Map/MapFactory.cpp
        # GUI/FACTORIES
        src/GUI/Factories/Button/ButtonFactory.cpp
        src/GUI/Factories/Label/LabelFactory.cpp
        src/GUI/Factories/TextInput/TextInputFactory.cpp
        src/GUI/Factories/KeyInput/KeyInputFactory.cpp
        src/GUI/Factories/Checkbox/CheckboxFactory.cpp
        src/GUI/Factories/Countdown/CountdownFactory.cpp
        src/GUI/Factories/Countdown/TimeText.cpp
        src/GUI/Factories/Image/ImageFactory.cpp
        src/GUI/Factories/Image/ImageSequenceFactory.cpp
        src/GUI/Factories/Slider/SliderFactory.cpp
        src/GUI/Factories/Inventory/InventoryFactory.cpp
        # IA
        src/Game/IABomberman/IABomberman.cpp
        src/Game/IABomberman/IACore.cpp
        # COMPONENTS
        src/Components/Render3D/Render3D.cpp
        src/Components/Render2D/Render2D.cpp
        src/Components/AbstractEvent/AbstractEvent.cpp
        src/Components/Hitbox/Hitbox.cpp
        src/Components/ClickEvent/ClickEvent.cpp
        src/Components/MouseMoveEvent/MouseMoveEvent.cpp
        src/Components/Chrono/Chrono.cpp
        src/Components/FocusEvent/ClickFocusEvent.cpp
        src/Components/TextInputConfig/TextInputConfig.cpp
        src/Components/Sound/Sound.cpp
        src/Components/PlayerConfig/PlayerConfig.cpp
        src/Components/Option/OptionComponent.cpp
        # SYSTEMS
        src/Systems/Render2D/Render2DSystem.cpp
        src/Systems/Render3D/Render3DSystem.cpp
        src/Systems/Hitbox/HitboxSystem.cpp
        src/Systems/Audio/AudioSystem.cpp
        src/Systems/Physics/PhysicsSystem.cpp
        src/Systems/PlayerConfig/PlayerConfigSystem.cpp
        # SCENES
        src/Scenes/DebugScene/DebugScene.cpp
        src/Scenes/MainMenu/MainMenuScene.cpp
        src/Scenes/OptionsMenu/OptionsMenuScene.cpp
        src/Scenes/SceneWithEvents/SceneWithEvents.cpp
        src/Scenes/SplashScreen/SplashScreenScene.cpp
        src/Scenes/KeyBindingMenu/KeyBindingMenuScene.cpp
        src/Scenes/PauseMenuScene/PauseMenuScene.cpp
        src/Scenes/LoadingScreen/LoadingScreenScene.cpp
        src/Scenes/GameScene/GameScene.cpp
        src/Scenes/SoundOption/SoundOptionScene.cpp
        # CONFIG
        src/ConfigFile/ConfigFile.cpp
        # EXCEPTION
        src/Exceptions/Exceptions.cpp
        # UTILITIES
        src/Utilities/utilities.cpp
        src/Utilities/ProportionUtilities.hpp
    )

add_executable(${NAME} ${SRCS})

if (MSVC)
    target_compile_options(${NAME} PRIVATE /W4 /WX)
else ()
    target_compile_options(${NAME} PRIVATE -Wall -Wextra -Wno-missing-field-initializers)
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