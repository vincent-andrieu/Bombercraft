/*
** EPITECH PROJECT, 2021
** indiestudio
** File description:
** KeyBox
*/

#ifndef KEYBOX_HPP_
#define KEYBOX_HPP_

#include "GameEngine.hpp"
#include "raylib.hpp"

namespace Component {
    class KeyBox : public Engine::Component<KeyBox> {
        public:
            KeyBox() : key(raylib::KeyBoard::IKEY_NULL)
            {
            }
            virtual ~KeyBox() = default;

            raylib::KeyBoard key;
        private:
        protected:

    };
}

#endif /* !KEYBOX_HPP_ */
