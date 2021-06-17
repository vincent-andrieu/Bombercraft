/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 28/05/2021 GameEngine.hpp.h
*/

#ifndef GAMEENGINE_HPP
#define GAMEENGINE_HPP

#include "env.hpp"
#include "entity.hpp"
#include "IComponentTypeRegister.hpp"

#include "Component/Component.hpp"
#include "ComponentTypeRegister/ComponentTypeRegister.hpp"
#include "EntityContainer/EntityRegister.hpp"
#include "EntityManager/EntityManager.hpp"
#include "AbstractSystem/AbstractSystem.hpp"
#include "SaveManager/SaveManager.hpp"

#include "components/Position.hpp"
#include "components/Velocity.hpp"
#include "components/Script.hpp"
#include "components/Timer.hpp"
#include "components/EntityBox.hpp"

#include "Systems/PhysicsSystem/PhysicsSystem.hpp"
#include "Systems/TimerSystem/TimerSystem.hpp"

#endif // GAMEENGINE_HPP