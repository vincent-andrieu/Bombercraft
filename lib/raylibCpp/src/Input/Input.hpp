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
        ~Input() override = default;
        [[nodiscard]] bool isKeyPressed(KeyBoard key) const override;
        [[nodiscard]] bool isKeyReleased(KeyBoard key) const override;
        [[nodiscard]] MyVector2 getMousePos() const override;
        [[nodiscard]] bool isMouseLeftPressed() const override;
        [[nodiscard]] bool isMouseRightPressed() const override;
        [[nodiscard]] bool isMouseMiddlePressed() const override;
        [[nodiscard]] bool isMouseMoved() override;
        [[nodiscard]] float getMouseWheel() const override;
        [[nodiscard]] bool MouseIsOver(MyVector2 pos, MyVector2 size) const override;
        [[nodiscard]] bool MouseIsOverClicked(MyVector2 pos, MyVector2 size) const override;

      private:
        MyVector2 _previousMousePos;
        std::unordered_map<KeyBoard, int> _keyList = {{raylib::KeyBoard::IKEY_A, KEY_Q},
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
            {raylib::KeyBoard::IKEY_M, KEY_SEMICOLON},
            {raylib::KeyBoard::IKEY_N, KEY_N},
            {raylib::KeyBoard::IKEY_O, KEY_O},
            {raylib::KeyBoard::IKEY_P, KEY_P},
            {raylib::KeyBoard::IKEY_Q, KEY_A},
            {raylib::KeyBoard::IKEY_R, KEY_R},
            {raylib::KeyBoard::IKEY_S, KEY_S},
            {raylib::KeyBoard::IKEY_T, KEY_T},
            {raylib::KeyBoard::IKEY_U, KEY_U},
            {raylib::KeyBoard::IKEY_V, KEY_V},
            {raylib::KeyBoard::IKEY_W, KEY_Z},
            {raylib::KeyBoard::IKEY_X, KEY_X},
            {raylib::KeyBoard::IKEY_Y, KEY_Y},
            {raylib::KeyBoard::IKEY_Z, KEY_W},
            {raylib::KeyBoard::IKEY_ZERO, KEY_ZERO},
            {raylib::KeyBoard::IKEY_ONE, KEY_ONE},
            {raylib::KeyBoard::IKEY_TWO, KEY_TWO},
            {raylib::KeyBoard::IKEY_THREE, KEY_THREE},
            {raylib::KeyBoard::IKEY_FOUR, KEY_FOUR},
            {raylib::KeyBoard::IKEY_FIVE, KEY_FIVE},
            {raylib::KeyBoard::IKEY_SIX, KEY_SIX},
            {raylib::KeyBoard::IKEY_SEVEN, KEY_SEVEN},
            {raylib::KeyBoard::IKEY_EIGHT, KEY_EIGHT},
            {raylib::KeyBoard::IKEY_NINE, KEY_NINE},
            {raylib::KeyBoard::IKEY_UP, KEY_UP},
            {raylib::KeyBoard::IKEY_DOWN, KEY_DOWN},
            {raylib::KeyBoard::IKEY_RIGHT, KEY_RIGHT},
            {raylib::KeyBoard::IKEY_LEFT, KEY_LEFT},
            {raylib::KeyBoard::IKEY_BACKSPACE, KEY_BACKSPACE},
            {raylib::KeyBoard::IKEY_SPACE, KEY_SPACE},
            {raylib::KeyBoard::IKEY_ESCAPE, KEY_ESCAPE},
            {raylib::KeyBoard::IKEY_ENTER, KEY_ENTER},
            {raylib::KeyBoard::IKEY_TAB, KEY_TAB},
            {raylib::KeyBoard::IKEY_INSERT, KEY_INSERT},
            {raylib::KeyBoard::IKEY_DELETE, KEY_DELETE},
            {raylib::KeyBoard::IKEY_PAGE_UP, KEY_PAGE_UP},
            {raylib::KeyBoard::IKEY_PAGE_DOWN, KEY_PAGE_DOWN},
            {raylib::KeyBoard::IKEY_HOME, KEY_HOME},
            {raylib::KeyBoard::IKEY_END, KEY_END},
            {raylib::KeyBoard::IKEY_CAPS_LOCK, KEY_CAPS_LOCK},
            {raylib::KeyBoard::IKEY_SCROLL_LOCK, KEY_SCROLL_LOCK},
            {raylib::KeyBoard::IKEY_NUM_LOCK, KEY_NUM_LOCK},
            {raylib::KeyBoard::IKEY_PRINT_SCREEN, KEY_PRINT_SCREEN},
            {raylib::KeyBoard::IKEY_PAUSE, KEY_PAUSE},
            {raylib::KeyBoard::IKEY_F1, KEY_F1},
            {raylib::KeyBoard::IKEY_F2, KEY_F2},
            {raylib::KeyBoard::IKEY_F3, KEY_F3},
            {raylib::KeyBoard::IKEY_F4, KEY_F4},
            {raylib::KeyBoard::IKEY_F5, KEY_F5},
            {raylib::KeyBoard::IKEY_F6, KEY_F6},
            {raylib::KeyBoard::IKEY_F7, KEY_F7},
            {raylib::KeyBoard::IKEY_F8, KEY_F8},
            {raylib::KeyBoard::IKEY_F9, KEY_F9},
            {raylib::KeyBoard::IKEY_F10, KEY_F10},
            {raylib::KeyBoard::IKEY_F11, KEY_F11},
            {raylib::KeyBoard::IKEY_F12, KEY_F12},
            {raylib::KeyBoard::IKEY_L_SHIFT, KEY_LEFT_SHIFT},
            {raylib::KeyBoard::IKEY_L_CTRL, KEY_LEFT_CONTROL},
            {raylib::KeyBoard::IKEY_L_ALT, KEY_LEFT_ALT},
            {raylib::KeyBoard::IKEY_L_SUPER, KEY_LEFT_SUPER},
            {raylib::KeyBoard::IKEY_R_SHIFT, KEY_RIGHT_SHIFT},
            {raylib::KeyBoard::IKEY_R_CTRL, KEY_RIGHT_CONTROL},
            {raylib::KeyBoard::IKEY_R_ALT, KEY_RIGHT_ALT},
            {raylib::KeyBoard::IKEY_R_SUPER, KEY_RIGHT_SUPER},
            {raylib::KeyBoard::IKEY_KP_0, KEY_KP_0},
            {raylib::KeyBoard::IKEY_KP_1, KEY_KP_1},
            {raylib::KeyBoard::IKEY_KP_2, KEY_KP_2},
            {raylib::KeyBoard::IKEY_KP_3, KEY_KP_3},
            {raylib::KeyBoard::IKEY_KP_4, KEY_KP_4},
            {raylib::KeyBoard::IKEY_KP_5, KEY_KP_5},
            {raylib::KeyBoard::IKEY_KP_6, KEY_KP_6},
            {raylib::KeyBoard::IKEY_KP_7, KEY_KP_7},
            {raylib::KeyBoard::IKEY_KP_8, KEY_KP_8},
            {raylib::KeyBoard::IKEY_KP_9, KEY_KP_9},
            {raylib::KeyBoard::IKEY_KP_DECIMAL, KEY_KP_DECIMAL},
            {raylib::KeyBoard::IKEY_KP_DIVIDE, KEY_KP_DIVIDE},
            {raylib::KeyBoard::IKEY_KP_MULTIPLY, KEY_KP_MULTIPLY},
            {raylib::KeyBoard::IKEY_KP_SUBTRACT, KEY_KP_SUBTRACT},
            {raylib::KeyBoard::IKEY_KP_ADD, KEY_KP_ADD},
            {raylib::KeyBoard::IKEY_KP_ENTER, KEY_KP_ENTER},
            {raylib::KeyBoard::IKEY_KP_EQUAL, KEY_KP_EQUAL}};
    };
}; // namespace raylib

#endif