/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 02/06/2021 Render2DSystem.cpp.cc
*/

#include "Render3D.hpp"

using namespace Component;

Render3D::Render3D(std::shared_ptr<raylib::I3DObject> object) : modele(object)
{
}