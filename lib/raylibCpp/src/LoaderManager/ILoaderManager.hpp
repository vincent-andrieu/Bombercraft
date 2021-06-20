/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** ILoaderManager
*/

#ifndef ILOADERMANAGER_HPP
#define ILOADERMANAGER_HPP

#include <string>

namespace raylib
{
    template <typename toLoadType, typename stringType>
    class ILoaderManager
    {
        public:
            virtual ~ILoaderManager() = default;
            virtual const toLoadType &load(const stringType &loadIn, std::string unique = "") = 0;
    };
};

#endif