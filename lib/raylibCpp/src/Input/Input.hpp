/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** Input
*/

#ifndef INPUT_HPP
#define INPUT_HPP

#include "IInput.hpp"
#include "object.hpp"

namespace raylib
{
    class Input : public IInput {
      public:
        Input();
        ~Input();
        bool isKeyPressed(KeyBoard key) const;
        bool isKeyReleased(KeyBoard key) const;
        MyVector2 getMousePos(void) const;
        bool isMouseLeftPressed(void) const;
        bool isMouseRightPressed(void) const;
        bool isMouseMiddlePressed(void) const;
        bool isMouseMoved(void);
        bool MouseIsOver(MyVector2 pos, MyVector2 size) const;
        bool MouseIsOverClicked(MyVector2 pos, MyVector2 size) const;

        private:
            MyVector2 _previousMousePos;
            std::unordered_map<KeyBoard, int> _keyList = {
                {raylib::KeyBoard::IKEY_A, KEY_A},
                {raylib::KeyBoard::IKEY_B, KEY_B},
                {raylib::KeyBoard::IKEY_C, KEY_C},
                {raylib::KeyBoard::IKEY_D, KEY_D},
                {raylib::KeyBoard::IKEY_E, KEY_E},
                {raylib::KeyBoard::IKEY_F, KEY_F},
                {raylib::KeyBoard::IKEY_G, KEY_G},
                {raylib::KeyBoard::IKEY_H, KEY_H},
                {raylib::KeyBoard::IKEY_I, KEY_I},
                {raylib::KeyBoard::IKEY_J, KEY_J},
                {raylib::KeyBoard::IKEY_K, KEY_K},
                {raylib::KeyBoard::IKEY_L, KEY_L},
                {raylib::KeyBoard::IKEY_M, KEY_M},
                {raylib::KeyBoard::IKEY_N, KEY_N},
                {raylib::KeyBoard::IKEY_O, KEY_O},
                {raylib::KeyBoard::IKEY_P, KEY_P},
                {raylib::KeyBoard::IKEY_Q, KEY_Q},
                {raylib::KeyBoard::IKEY_R, KEY_R},
                {raylib::KeyBoard::IKEY_S, KEY_S},
                {raylib::KeyBoard::IKEY_T, KEY_T},
                {raylib::KeyBoard::IKEY_U, KEY_U},
                {raylib::KeyBoard::IKEY_V, KEY_V},
                {raylib::KeyBoard::IKEY_W, KEY_W},
                {raylib::KeyBoard::IKEY_X, KEY_X},
                {raylib::KeyBoard::IKEY_Y, KEY_Y},
                {raylib::KeyBoard::IKEY_Z, KEY_Z},
                {raylib::KeyBoard::IKEY_UP, KEY_UP},
                {raylib::KeyBoard::IKEY_DOWN, KEY_DOWN},
                {raylib::KeyBoard::IKEY_RIGHT, KEY_RIGHT},
                {raylib::KeyBoard::IKEY_LEFT, KEY_LEFT},
            };
    };
}; // namespace raylib

#endif