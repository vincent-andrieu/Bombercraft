/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** ShaderManage
*/

#ifndef SHADERMANAGE_HPP
#define SHADERMANAGE_HPP

#include "IShaderManage.hpp"
#include "../../include/object.hpp"
#include <filesystem>
#include <unordered_map>

#include "export.hpp"

namespace raylib
{
    class EXPORT ShaderManage : public IShaderManage {
      public:
        ShaderManage();
        ~ShaderManage();
        void startShaderMode(string shaderName) const;
        void endShaderMode() const;
        void addShader(string filepath, string shaderName = "");
        void removeShader(string shaderName);

      private:
        std::unordered_map<string, Shader> _shaderList;
    };
}; // namespace raylib

#endif