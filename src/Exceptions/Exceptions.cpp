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