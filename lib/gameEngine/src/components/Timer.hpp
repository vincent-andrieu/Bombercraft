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
#include <chrono>

namespace Engine
{
    #define NOW (((double)std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count()) / 1000.0f)

    class Timer : public Component<Timer> {
      public:
        Timer(double seconds, EntityManager &entityManager, SceneManager &sceneManager, scriptHandler handler);
        virtual ~Timer() = default;

        void start();

        bool eval(Entity entity);

        void pause();
        void resume();
        bool isPaused() const;

        [[nodiscard]] double getDelta() const;

        bool save(SaveManager &saver) const override;
        bool load(SaveManager &saver) override;

      public:
        double interval;    // in seconds
        double startTime;   // in seconds
        Script script;

      private:
        bool _inPause;
        double _savedDuration;
    };
} // namespace Engine

#endif // TIMER_HPP