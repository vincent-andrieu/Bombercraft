/*
 * EPITECH PROJECT, 2021
 * include
 * File description:
 * I3DObject.hpp - Created: 10/06/2021
 */

#ifndef I3DOBJECT_HPP
#define I3DOBJECT_HPP

#include "IRenderable.hpp"
#include "IMovable.hpp"

namespace raylib
{
    class I3DObject : public IRenderable, public IMovable {
    };
} // namespace raylib

#endif