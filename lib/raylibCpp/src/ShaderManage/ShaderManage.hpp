/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** ShaderManage
*/

#ifndef SHADERMANAGE_HPP
#define SHADERMANAGE_HPP

#include "IShaderManage.hpp"
#include "../../include/include.hpp"
#include <unistd.h>
#include <unordered_map>

namespace raylib
{
    class ShaderManage : public IShaderManage
    {
        public :
            ShaderManage();
            ~ShaderManage();
            void startShaderMode(std::string shaderName) const;
            void endShaderMode() const;
            void addShader(std::string filepath, std::string shaderName = "");
            void removeShader(std::string shaderName);
        
        private:
            std::unordered_map<std::string, Shader> _shaderList;
    };
};

#endif