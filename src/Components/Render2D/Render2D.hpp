/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 02/06/2021 Render2D.hpp.h
*/

#ifndef RENDER2D_HPP
#define RENDER2D_HPP

#include "GameEngine.hpp"
#include "raylib.hpp"
#include <memory>
#include <vector>
#include <unordered_map>
#include <map>
#include <set>

namespace Component
{
    using render2dMapModels = std::vector<std::pair<std::string, std::shared_ptr<raylib::IRenderable>>>;

    class Render2D : public Engine::Component<Render2D> {
      public:
        explicit Render2D(render2dMapModels const &models);
        ~Render2D() = default;

        void draw();

        void add(std::shared_ptr<raylib::IRenderable> model, const std::string &label);
        void remove(const std::string &label);

        std::shared_ptr<raylib::IRenderable> &get(const std::string &label);
        bool doesGet(const std::string &label);

        void unsetToDraw(const std::string &label);
        void setToDrawFirst(const std::string &label);
        void setToDrawLast(const std::string &label);
        bool isSetToDraw(const std::string &label) const;

      protected:
        std::vector<std::shared_ptr<raylib::IRenderable>> _models;
        std::unordered_map<std::string, std::size_t> _modelIndex;
        std::unordered_map<std::size_t, std::string> _labelIndex;
        std::set<std::size_t> _modelsToDrawIndex;
    };
} // namespace Component

#endif // RENDER2D_HPP