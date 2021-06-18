/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 14/06/2021 OptionComponent.cpp.cc
*/

#include "OptionComponent.hpp"

Component::OptionComponent::OptionComponent(float volumeMusic, float volumeEffects, const std::string &ressourcePack, float fov)
    : volumeEffects(volumeEffects), volumeMusic(volumeMusic), ressourcePack(ressourcePack), fov(fov)
{
}
