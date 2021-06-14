/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 04/06/2021 SceneLoader.hpp.h
*/

#ifndef SCENELOADER_HPP
#define SCENELOADER_HPP

#include "raylib.hpp"
#include "GameEngine.hpp"

#include "ConfigFile/ConfigFile.hpp"

#define CONFIG_FILE "bomberman.config"
#define UNUSED      [[maybe_unused]]

#include <thread>
#include <mutex>

namespace Game
{
    class SceneLoader {
      public:
        SceneLoader() = delete;
        ~SceneLoader() = delete;

        template <typename T> static void setScene();
    };

    template <typename T> void SceneLoader::setScene()
    {
        bool loaded = false;
        std::shared_ptr<Engine::AbstractScene> loadingScene = CoreData::sceneManager->getScene<LoadingScreenScene>();
        std::mutex lock;

        std::thread thread([&lock, &loaded, &loadingScene]() {
            lock.lock();
            loadingScene->open();
            while (CoreData::_window->isOpen() && !loaded) {
                CoreData::_window->clear();
                CoreData::sceneManager->run(loadingScene);
                CoreData::_window->refresh();
            }
            loadingScene->close();
            lock.unlock();
        });
        loaded = true;
        thread.join();
        CoreData::sceneManager->setScene<T>();
        CoreData::sceneManager->updateScene();
    };
} // namespace Game

#define CONF_GET_COLOR(label) static_cast<raylib::RColor>(CoreData::settings->getInt(label))

#endif // SCENELOADER_HPP