/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 27/05/2021 EntityContainer.hpp.h
*/

#ifndef ENTITYCONTAINER_HPP
#define ENTITYCONTAINER_HPP

#include <vector>
#include <bitset>
#include <cstddef>
#include <numeric>
#include "env.hpp"
#include "entity.hpp"

class EntityContainer {
  public:
    EntityContainer() = default;
    ~EntityContainer() = default;

    void reserve(std::size_t size);
    std::vector<std::bitset<MAX_COMPONENT>> &getEntityToBitset();
    const std::bitset<MAX_COMPONENT> &getBitset(Entity entity) const;
    Entity create();
    void remove(Entity entity);

  private:
    std::vector<std::bitset<MAX_COMPONENT>> _entityToBitset;
    std::vector<Entity> _freeEntities;
};

#endif // ENTITYCONTAINER_HPP
