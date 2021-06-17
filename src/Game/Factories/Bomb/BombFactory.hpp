/*
** EPITECH PROJECT, 2021
** indiestudio
** File description:
** BombFactory
*/

#ifndef BOMBFACTORY_HPP_
#define BOMBFACTORY_HPP_

#include "GameEngine.hpp"
#include "EntityPack/EntityPack.hpp"
#include "Systems/Render2D/Render2DSystem.hpp"
#include "Systems/Render3D/Render3DSystem.hpp"

namespace GUI
{
    class BombFactory {
      public:
        BombFactory() = delete;
        ~BombFactory() = delete;
        static Engine::Entity create(Engine::EntityPack &entityPack,
            const raylib::MyVector3 position,
            Engine::Entity entityParent,
            const std::string &name = "");
        static bool placeBomb(Engine::Entity character);
        static bool placeBomb(
            Engine::Entity character, const raylib::MyVector3 &characterPosition, const float characterOrientation);

      protected:
      private:
        static std::shared_ptr<raylib::Model> getModel(const raylib::MyVector3 &pos);

        static void handlerBombTimer(
            Engine::EntityManager &entityManager, Engine::SceneManager &sceneManager, const Engine::Entity &entity);
        static void handlerBombCollision(const Engine::Entity &fromEntity, const Engine::Entity &toEntity);

        static raylib::MyVector2 getNextPos(const raylib::MyVector2 &position, const float rotation);
        static bool isBombPlacable(float posX, float posY);
    };
} // namespace GUI

#endif /* !BOMBFACTORY_HPP_ */