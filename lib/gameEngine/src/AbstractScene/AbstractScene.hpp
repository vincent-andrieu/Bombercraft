/*
** EPITECH PROJECT, 2021
** indiestudio
** File description:
** AbstractScene
*/

#ifndef ABSTRACTSCENE_HPP_
#define ABSTRACTSCENE_HPP_

#include "EntityManager/EntityManager.hpp"
#include "SystemManager/SystemManager.hpp"

namespace Engine
{
    class AbstractScene {
      public:
        AbstractScene(SystemManager &systemManager, EntityManager &entityManager);
        ~AbstractScene();

        virtual void update() = 0;

      protected:
        SystemManager &_systemManager;
        EntityManager &_entityManager;
    };
}

#endif /* !ABSTRACTSCENE_HPP_ */
