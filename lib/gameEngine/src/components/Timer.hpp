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
    class Timer : public Component<Timer> {
      public:
        Timer(std::size_t time, EntityManager &entityManager, SceneManager &sceneManager, scriptHandler &handler)
            : interval(time), startTime(std::chrono::system_clock::now()), script(entityManager, sceneManager, handler)
        {
        }
        ~Timer() = default;

        void start()
        {
            startTime = std::chrono::system_clock::now();
        }

        bool eval(Entity entity)
        {
            std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
            std::chrono::milliseconds t =
                std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch() - startTime.time_since_epoch());

            if (t >= interval) {
                startTime = std::chrono::system_clock::now();
                script.trigger(entity);
                return true;
            }
            return false;
        }

        void save(SaveManager &saver) const override
        {
            try {
                saver.closeWritingFile();
            } catch (const std::filesystem::filesystem_error &my_e) {
                SaveManager::printException(my_e);
            }
        }
        void load(SaveManager &saver) override
        {
            try {
                saver.closeReadingFile();
            } catch (const std::filesystem::filesystem_error &my_e) {
                SaveManager::printException(my_e);
            }
        }
        std::chrono::milliseconds interval;
        std::chrono::system_clock::time_point startTime;
        Script script;
    };
} // namespace Engine

#endif // TIMER_HPP