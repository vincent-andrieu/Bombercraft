/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 02/06/2021 Render3DSystem.hpp.h
*/

#ifndef MODEL_LIST_SYS_T
#define MODEL_LIST_SYS_T

#include "GameEngine.hpp"
#include "Components/ModelList/ModelList.hpp"

namespace System
{
    class ModelListSystem : public Engine::AbstractSystem {
      public:
        ModelListSystem();

        void update();
    };
} // namespace System

#endif // MODEL_LIST_SYS_T
