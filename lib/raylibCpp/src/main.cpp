/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** Main Test
*/

#include "raylib.hpp"

int main(void)
{
    MyVector2 windowSize(1200, 800);
    MyVector3 camPos(0, -5.0f, 10.0f);
    MyVector3 camTarget(0, 0, 0);
    MyVector3 camUp(0.0f, 1.0f, 0.0f);
    MyVector3 cubePos(0, 0, 0);
    MyVector3 cubeSize(2.0f, 2.0f, 2.0f);
    std::shared_ptr<IWindow> window = std::make_shared<raylib::Window>(Window(windowSize, "Bootstrap", raylib::RColor::RWHITE));
    std::shared_ptr<IInput> input = std::make_shared<raylib::Input>(Input());
    std::shared_ptr<ICamera> camera = std::make_shared<raylib::Camera>(raylib::Camera(camPos, camTarget, camUp));
    std::shared_ptr<ISolid> cube = std::make_shared<raylib::Cuboid>(Cuboid(nullptr, cubePos, cubeSize, raylib::RColor::RGREEN));

    window->setCamera(camera);
    window->open();
    while (window->isOpen()) {
        window->clear();
        if (input->isKeyPressed(raylib::KeyBoard::IKEY_W)) {
            windowSize.a += 100;
            windowSize.b += 100;
            window->setSize(windowSize);
            window->setColor(raylib::RColor::RBLUE);
        }
        if (input->isKeyPressed(raylib::KeyBoard::IKEY_Q)) {
            windowSize.a -= 100;
            windowSize.b -= 100;
            window->setSize(windowSize);
            window->setColor(raylib::RColor::RRED);
        }
        camera->begin3D();
        cube->draw();
        camera->end3D();
        window->refresh();
    }
    window->close();
    return 0;
}