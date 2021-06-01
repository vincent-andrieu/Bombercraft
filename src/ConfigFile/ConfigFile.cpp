/*
** EPITECH PROJECT, 2021
** indiestudio
** File description:
** ConfigFile
*/

#include "ConfigFile.hpp"

ConfigFile::ConfigFile()
{
}

ConfigFile::ConfigFile(const std::string &filename)
{
    this->loadFile(filename);
}

ConfigFile::~ConfigFile()
{
}

void ConfigFile::loadFile(const std::string &filename)
{
    std::string line;
    std::ifstream myfile (filename);
    std::regex isAscii ("^[\\x00-\\x7F]+$");

    if (myfile.is_open()) {
        while (getline(myfile, line)) {
            if (!std::regex_search(line, isAscii)) {
                throw ParserExceptions("The file doesn't contains only ASCII characters !");
            } else {
                this->commentManagingLine(line);
            }
        }
    } else {
        throw std::invalid_argument("File close");
    }
    for (auto it : this->_fileContent) {
        std::cout << it << std::endl;
    }
    
}

int ConfigFile::getInt(const std::string name) const
{
    return 0;
}

float ConfigFile::getFloat(const std::string name) const
{
    return 0.0;
}

std::string ConfigFile::getString(const std::string name) const
{
    return std::string("");
}

void ConfigFile::commentManagingLine(std::string line)
{
    size_t tofind = line.find('#');

    if (tofind != std::string::npos)
        line = line.substr(0, tofind);
    if (!line.empty() && tofind) {
        this->cleanLine(line);
        this->_fileContent.push_back(line);
    }
}

void ConfigFile::cleanLine(std::string &str)
{
    std::string::iterator next;

    for (std::string::iterator it = str.begin(); it != str.end();) {
        next = it + 1;
        if ((*it) == ' ' && it == str.begin()) {
            str.erase(it);
        } else if ((*it) == ' ' && next == str.end()) {
            str.erase(it);
        } else if ((*it) == ' ' && (*next) == ' ') {
            str.erase(it);
        } else
            it++;
    }
}