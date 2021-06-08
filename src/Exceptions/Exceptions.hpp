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
        ~ParserExceptions();

        const char *what() const noexcept override;
        private:
            std::string _message;
};

class IAExceptions : public std::exception
{
    public:
        IAExceptions(std::string const &message, bool fatal = true);
        ~IAExceptions();
        const char *what() const noexcept override;
        bool isFatalThrow() const;

        private:
            std::string _message;
            bool _fatal;
};

#endif /* !EXCEPTIONS_HPP_ */
