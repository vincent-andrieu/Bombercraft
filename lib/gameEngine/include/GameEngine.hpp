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

#include "components/Position.hpp"
#include "components/Velocity.hpp"

#include "system/PhysicsSystem/PhysicsSystem.hpp"

typedef std::string string;
typedef std::size_t size_t;
typedef std::stringstream stringstream;
typedef std::fstream fstream;
typedef std::ofstream ofstream;
typedef std::ifstream ifstream;
#define charette_ptr(T) std::shared_ptr<T>
#define toString(str)   std::to_string(str)
#define toInteger(str)  std::stoi(str)
#define toSize_t(str)   std::stoul(str)

#endif // GAMEENGINE_HPP