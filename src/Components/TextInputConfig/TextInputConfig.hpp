/*
** EPITECH PROJECT, 2021
** indiestudio
** File description:
** TextInputConfig
*/

#ifndef TEXTINPUTCONFIG_HPP_
#define TEXTINPUTCONFIG_HPP_

#include "GameEngine.hpp"

namespace Component {
    class TextInputConfig : public Engine::Component<TextInputConfig> {
        public:
            TextInputConfig(size_t maxChar);
            ~TextInputConfig();

            size_t getMaxChar() const;
        protected:
        private:
            size_t _maxChar;
    };
}

#endif /* !TEXTINPUTCONFIG_HPP_ */
