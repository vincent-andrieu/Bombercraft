/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** ShaderManage.cpp
*/

#include "ShaderManage.hpp"

using namespace raylib;

namespace fs = std::filesystem;

ShaderManage::ShaderManage() : _shaderList()
{
}

ShaderManage::~ShaderManage()
{
    for (auto it : this->_shaderList)
        UnloadShader(it.second);
    this->_shaderList.clear();
}

void ShaderManage::startShaderMode(string shaderName) const
{
    std::unordered_map<string, Shader>::const_iterator it = this->_shaderList.find(shaderName);

    if (it == this->_shaderList.end())
        throw std::invalid_argument("Shader " + shaderName + "are not loaded.");
    BeginShaderMode(it->second);
}

void ShaderManage::endShaderMode() const
{
    EndShaderMode();
}

void ShaderManage::addShader(string filepath, string shaderName)
{
    fs::path filepathShader(filepath);
    std::unordered_map<string, Shader>::const_iterator it = this->_shaderList.find(shaderName);

    if (shaderName == "")
        shaderName = filepath;
    if (it == this->_shaderList.end())
        throw std::invalid_argument("Shader " + shaderName + "already exist.");
    if (fs::exists(filepathShader) == false)
        throw std::invalid_argument("Filepath incorrect: " + filepath);
    this->_shaderList[shaderName] = LoadShader(NULL, TextFormat(filepath.c_str(), GLSL_VERSION));
}

void ShaderManage::removeShader(string shaderName)
{
    std::unordered_map<string, Shader>::const_iterator it = this->_shaderList.find(shaderName);

    if (it == this->_shaderList.end())
        throw std::invalid_argument("Shader " + shaderName + "didn't exist.");
    UnloadShader(it->second);
    this->_shaderList.erase(it);
}