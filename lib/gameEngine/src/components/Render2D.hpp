/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 02/06/2021 Render2D.hpp
*/

#ifndef RENDER2D_HPP
#define RENDER2D_HPP

#include "Component/Component.hpp"

namespace Engine
{
    template <typename T, typename... Args> class Render2D : public Component<Render2D<T, Args>> {
      public:
        Render2D(Args &&...args) : _modele(std::forward(args)...)
        {
        }
        ~Render2D() = default;

        T modele;
    };
}

#endif // RENDER2D_HPP
