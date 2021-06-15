/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 15/06/2021 ModelList.hpp.h
*/

#ifndef MODELLIST_HPP
#define MODELLIST_HPP

#include "raylib.hpp"
#include "GameEngine.hpp"

#include <vector>
#include <unordered_map>

namespace Component
{
    using ModelListMap = std::unordered_map<std::string, std::shared_ptr<raylib::IModel>>;

    class ModelList : public Engine::Component<ModelList> {
      public:
        ModelList(std::unordered_map<std::string, std::shared_ptr<raylib::IModel>> const &models, std::string const &firstModel);
        virtual ~ModelList() = default;

        void select(std::string const &label);
        void draw();
        void setPosition(const raylib::MyVector3 position);
        void setRotation(const raylib::MyVector3 rotation);
        void setTexture(std::string const &path);

        const raylib::MyVector3 &getPosition() const;
        void setScale(const float scale);

      private:
        std::vector<std::shared_ptr<raylib::IModel>> _models;
        std::unordered_map<std::string, std::size_t> _modelNames;
        std::shared_ptr<raylib::IModel> _selected;
    };
} // namespace Component

#endif // MODELLIST_HPP
