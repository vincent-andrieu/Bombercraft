/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 02/06/2021 Render3D.hpp.h
*/

#ifndef RENDER3D_HPP
#define RENDER3D_HPP

#include "Component/Component.hpp"

namespace Engine
{
    template <typename T, typename... Args> class Render3D : public Component<Render3D<T, Args>> {
      public:
        Render3D(Args &&...args) : _modele(std::forward(args)...)
        {
        }
        ~Render3D() = default;

        T modele;
    };
}

#endif // RENDER3D_HPP
