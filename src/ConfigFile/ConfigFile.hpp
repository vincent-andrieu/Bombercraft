/*
** EPITECH PROJECT, 2021
** indiestudio
** File description:
** ConfigFile
*/

#ifndef CONFIGFILE_HPP_
#define CONFIGFILE_HPP_

#include "IConfigFile.hpp"
#include "../Exceptions/Exceptions.hpp"

class ConfigFile : public IConfigFile
{
    public:
        ConfigFile();
        ConfigFile(const std::string &filename);
        ~ConfigFile();
        void loadFile(const std::string &filename);
        int getInt(const std::string name) const;
        float getFloat(const std::string name) const;
        std::string getString(const std::string name) const;

    private:
        void cleanLine(std::string &str);
        void commentManagingLine(std::string line);

    protected:
    private:
        std::vector<std::string> _fileContent;
};

#endif /* !CONFIGFILE_HPP_ */
