/*
** EPITECH PROJECT, 2021
** ARender2D.hpp
** File description:
** Abstract class to render 2D objects
*/
#ifndef BOMBERMAN_ARENDER2D_HPP
#define BOMBERMAN_ARENDER2D_HPP

#include "GameEngine.hpp"
#include "raylib.hpp"
#include <memory>
#include <vector>
#include <unordered_map>

namespace Component
{
    using render2dMapModels = std::unordered_map<std::string, std::shared_ptr<raylib::IRenderable>>;

    class ARender2D {
      public:
        explicit ARender2D(render2dMapModels const &models);
        ~ARender2D() = default;

        void add(std::shared_ptr<raylib::IRenderable> model, const std::string &label);
        void remove(const std::string &label);

        virtual void draw() = 0;

        std::shared_ptr<raylib::IRenderable> &get(const std::string &label);

        virtual bool save(Engine::SaveManager &saver) const = 0;
        virtual bool load(Engine::SaveManager &saver) = 0;

      protected:
        std::vector<std::shared_ptr<raylib::IRenderable>> _models;
        std::unordered_map<std::string, std::size_t> _modelIndex;
        std::unordered_map<std::size_t, std::string> _labelIndex;
    };
} // namespace Component

#endif // BOMBERMAN_ARENDER2D_HPP