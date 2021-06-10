/*
** EPITECH PROJECT, 2021
** indiestudio
** File description:
** utilities
*/

#ifndef UTILITIES_HPP_
#define UTILITIES_HPP_

#include "GUI/Factories/Label/LabelFactory.hpp"
#include "EntityManager/EntityManager.hpp"
#include "Game/Core/Core.hpp"
#include "Game/CoreData/CoreData.hpp"

std::string getPromptContent(Engine::EntityPack &pack, std::string inputName);
raylib::KeyBoard getKeyInputContent(Engine::EntityPack &pack, std::string keyInputName);

#endif /* !UTILITIES_HPP_ */
