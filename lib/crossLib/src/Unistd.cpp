/*
** EPITECH PROJECT, 2021
** indiestudio
** File description:
** Unistd
*/

#include "Unistd.hpp"

using namespace Cross;

int Unistd::my_access(const std::string &pathname, const aMode mode) noexcept
{
#ifdef __linux__
    return access(pathname.c_str(), mode);
#elif _WIN32
    return _access(pathname.c_str(), mode);
#endif   
}
