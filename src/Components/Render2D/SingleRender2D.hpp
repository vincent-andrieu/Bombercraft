/*
** EPITECH PROJECT, 2021
** SingleRender2D.hpp
** File description:
** Class allowing to handle several render elements, but render a single
*/
#ifndef BOMBERMAN_SINGLERENDER2D_HPP
#define BOMBERMAN_SINGLERENDER2D_HPP

#include "ARender2D.hpp"

namespace Component
{
    class SingleRender2D : public ARender2D, public Engine::Component<SingleRender2D> {
      public:
        explicit SingleRender2D(render2dMapModels const &models);
        ~SingleRender2D() = default;

        void draw() override;

        void setActRender2D(const std::string &label);

        bool save(Engine::SaveManager &saver) const override;
        bool load(Engine::SaveManager &saver) override;

      private:
        std::size_t _actRender2D{0};
    };
} // namespace Component

#endif // BOMBERMAN_SINGLERENDER2D_HPP