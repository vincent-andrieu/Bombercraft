/*
** EPITECH PROJECT, 2021
** indiestudio
** File description:
** Exceptions
*/

#include "Exceptions.hpp"

ParserExceptions::ParserExceptions(std::string const &message) :
    _message(message)
{
}

ParserExceptions::~ParserExceptions()
{
}

const char *ParserExceptions::what() const noexcept
{
    return _message.c_str();
}

IAExceptions::IAExceptions(std::string const &message, bool fatal) :
_message(message), _fatal(fatal)
{
}

IAExceptions::~IAExceptions()
{
}

const char *IAExceptions::what() const noexcept
{
    return _message.c_str();
}

bool IAExceptions::isFatalThrow() const
{
    return this->_fatal;
}