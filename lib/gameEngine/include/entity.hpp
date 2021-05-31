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

using Entity = uint32_t;

using Index = uint32_t;

static constexpr auto InvalidIndex = std::numeric_limits<Index>::max();

#endif // ENTITY_HPP
