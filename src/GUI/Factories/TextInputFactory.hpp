/*
** EPITECH PROJECT, 2021
** indiestudio
** File description:
** TextInputFactory
*/

#ifndef TEXTINPUTFACTORY_HPP_
#define TEXTINPUTFACTORY_HPP_

#include "raylib.hpp"

#include "Game/CoreData/CoreData.hpp"

#include "Components/Render2D/Render2D.hpp"
#include "Scenes/SceneWithEvents/SceneWithEvents.hpp"
#include "Game/EventRequirement/EventRequirement.hpp"
#include "GameEngine.hpp"

namespace GUI
{
    struct TextInputConfig {
        const std::size_t size;
    };

    class TextInputFactory {
        public:
            ~TextInputFactory() = delete;

            static void create(Engine::EntityPack &pack, TextInputConfig const &config);

        protected:
        private:
    };
} // namespace GUI

#endif /* !TEXTINPUTFACTORY_HPP_ */
