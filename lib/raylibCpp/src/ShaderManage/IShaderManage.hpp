/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** IShaderManage
*/

#ifndef ISHADERMANAGE_HPP
#define ISHADERMANAGE_HPP

#include "../../include/include.hpp"

namespace raylib
{
    class IShaderManage
    {
        public :
            virtual ~IShaderManage() = default;
            virtual void startShaderMode(std::string shaderName) const = 0;
            virtual void endShaderMode() const = 0;
            virtual void addShader(std::string filepath, std::string shaderName = "") = 0;
            virtual void removeShader(std::string shaderName) = 0;
    };
};

#endif