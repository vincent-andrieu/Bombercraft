/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 27/05/2021 IComponentContainer.hpp.h
*/

#ifndef ICOMPONENTCONTAINER_HPP
#define ICOMPONENTCONTAINER_HPP

#include <cstddef>
#include "entity.hpp"

class IComponentContainer {
  public:
    virtual ~IComponentContainer() = default;

    virtual void reserve(std::size_t size) = 0;
    virtual bool tryRemove(Entity entity) = 0;
};

#endif // ICOMPONENTCONTAINER_HPP
