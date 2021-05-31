/*
** EPITECH PROJECT, 2021
** indiestudio
** File description:
** IEventManager
*/

#ifndef IEVENTMANAGER_HPP_
#define IEVENTMANAGER_HPP_

#include <vector>

class IEventManager {
    public:

        virtual ~IEventManager() = default;

        virtual bool isKeyPressed(int key) = 0;
        virtual bool isKeyReleased(int key) = 0;

        virtual bool isMouseMoved() = 0;
        virtual bool isMouseLeftClick() = 0;
        virtual bool isMouseRightClick() = 0;
        virtual bool isMouseMiddleClick() = 0;

        std::vector<int> getMousePos();
};

#endif /* !IEVENTMANAGER_HPP_ */
