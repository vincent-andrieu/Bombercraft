/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 27/05/2021 entity.hpp.h
*/

#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <cstdint>
#include <limits>
#include <bitset>
#include "env.hpp"

namespace Engine
{
    using Entity = uint32_t;

    using Index = uint32_t;

    static constexpr auto InvalidIndex = std::numeric_limits<Index>::max();

    typedef std::bitset<MAX_COMPONENT> Signature;
}

typedef std::bitset<MAX_COMPONENT> Signature;

#endif // ENTITY_HPP
