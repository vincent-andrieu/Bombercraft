/*
** EPITECH PROJECT, 2021
** indiestudio
** File description:
** Exceptions
*/

#ifndef EXCEPTIONS_HPP_
#define EXCEPTIONS_HPP_

#include <exception>
#include <string>

class ParserExceptions : public std::exception {
    public:
        ParserExceptions(std::string const &message);

        const char *what() const noexcept override;
        private:
            std::string _message;
};

#endif /* !EXCEPTIONS_HPP_ */
