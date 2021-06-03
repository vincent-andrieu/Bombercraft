/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** IShaderManage
*/

#ifndef ISHADERMANAGE_HPP
#define ISHADERMANAGE_HPP

#include "../../include/object.hpp"

#include "export.hpp"

namespace raylib
{
    class EXPORT IShaderManage {
      public:
        virtual ~IShaderManage() = default;
        virtual void startShaderMode(string shaderName) const = 0;
        virtual void endShaderMode() const = 0;
        virtual void addShader(string filepath, string shaderName = "") = 0;
        virtual void removeShader(string shaderName) = 0;
    };
}; // namespace raylib

#endif