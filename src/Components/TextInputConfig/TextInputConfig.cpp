/*
** EPITECH PROJECT, 2021
** indiestudio
** File description:
** TextInputConfig
*/

#include "TextInputConfig.hpp"

using namespace Component;

TextInputConfig::TextInputConfig(size_t maxChar) :
    _maxChar(maxChar)
{
}

TextInputConfig::~TextInputConfig()
{
}

size_t TextInputConfig::getMaxChar() const
{
    return _maxChar;
}
