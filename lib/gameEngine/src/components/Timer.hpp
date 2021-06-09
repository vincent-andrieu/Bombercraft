/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 02/06/2021 Timer.hpp.h
*/

#ifndef TIMER_HPP
#define TIMER_HPP

#include "Component/Component.hpp"
#include "Script.hpp"
#include <ctime>

namespace Engine
{
    #define NOW ((static_cast<double>(clock()) / CLOCKS_PER_SEC) * 10.0f)

    class Timer : public Component<Timer> {
      public:
        Timer(double seconds, EntityManager &entityManager, SceneManager &sceneManager, scriptHandler handler);
        virtual ~Timer() = default;

        void start();

        bool eval(Entity entity);

        [[nodiscard]] double getDelta() const;

        bool save(SaveManager &saver) const override;
        bool load(SaveManager &saver) override;

        double interval;    // in seconds
      protected:
        double startTime;   // in seconds
        Script script;
    };
} // namespace Engine

#endif // TIMER_HPP