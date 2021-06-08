/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 07/06/2021 ButtonFactory.hpp.h
*/

#ifndef BUTTONFACTORY_HPP
#define BUTTONFACTORY_HPP

#include "raylib.hpp"

#include "IFactoryData.hpp"
#include "Game/CoreData/CoreData.hpp"

#include "Components/ClickEvent.hpp"
#include "Components/MouseMoveEvent.hpp"
#include "Components/Render2D/Render2D.hpp"

namespace GUI
{
    //    class ButtonStaticConfig : public IStaticFactoryData {
    //      public:
    //        ButtonStaticConfig(std::string const &texturePath, raylib::MyVector2 const &size, std::size_t fontSize,
    //            raylib::RColor fontColor, std::string const &fontPath, const EventRequirement &requirements);
    //
    //        std::string texturePath;
    //        raylib::MyVector2 size;
    //        std::size_t fontSize;
    //        raylib::RColor fontColor;
    //        std::string fontPath;
    //        EventRequirement requirements;
    //    };
    //
    //    class ButtonDynamicConfig : public IDynFactoryData {
    //      public:
    //        ButtonDynamicConfig(raylib::MyVector2 const &position, std::string const &label, Component::eventScript &handler);
    //
    //        raylib::MyVector2 position;
    //        std::string label;
    //        Component::eventScript &handler;
    //    };
    //
    //    const auto buttonFactory = [](Engine::EntityPack &pack, IStaticFactoryData const &staticData,
    //                                   IDynFactoryData const &dynamicData) {
    //        Engine::Entity entity = pack.createAnonymousEntity();
    //        const auto &staticConf = *dynamic_cast<const ButtonStaticConfig *>(&staticData);
    //        const auto &dynConf = *dynamic_cast<const ButtonDynamicConfig *>(&dynamicData);
    //
    //        CoreData::entityManager->addComponent<Component::ClickEvent>(entity, dynConf.handler);
    //        CoreData::entityManager->addComponent<Component::MouseMoveEvent>(entity, dynConf.handler, staticConf.requirements);
    //        CoreData::entityManager->addComponent<Component::Render2D>(entity,
    //            Component::render2dMapModels{
    //                {"background", std::make_shared<raylib::Texture>(staticConf.texturePath, dynConf.position)}});
    //        return entity;
    //    };

    struct ButtonConfig {
        const std::string idleTexturePath;
        const std::string hoverTexturePath;
        const std::string clickedTexturePath;
        const std::string unavailableTexturePath;
        const raylib::MyVector2 size;
        const std::size_t fontSize;
        const raylib::RColor fontColor;
        const std::string fontPath;
        const Game::EventRequirement requirements;
    };

    class ButtonFactory {
      public:
        virtual ~ButtonFactory() = 0;

        /**
         * @brief
         * @throw If configuration file information retrieval fails
         * @return
         */
        static ButtonConfig standardButton();

        static void create(Engine::EntityPack &pack,
            raylib::MyVector2 &position,
            string const &label,
            Component::eventScript &handler,
            ButtonConfig const &conf);
    };
} // namespace GUI

#endif // BUTTONFACTORY_HPP