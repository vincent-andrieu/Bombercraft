/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 11/06/2021 StringChoice.hpp.h
*/

#ifndef STRINGCHOICE_HPP
#define STRINGCHOICE_HPP

#include "GameEngine.hpp"
#include <vector>

namespace Component
{
    class StringChoice : public Engine::Component<StringChoice> {
      public:
        StringChoice(std::vector<std::string> const &choices);
        virtual ~StringChoice() = default;

        std::string get() const;
        void next();
        void prev();

      private:
        std::size_t _idx;
        std::vector<std::string> _choices;
    };
}

#endif // STRINGCHOICE_HPP
