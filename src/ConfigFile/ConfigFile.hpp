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
        ConfigFile(std::vector<std::string> tab);
        ~ConfigFile();
        int getInt(const std::string name) const;
        void loadFile(const std::string &filename);
        float getFloat(const std::string name) const;
        std::string getString(const std::string name) const;
        std::pair<int, int> getPaire(const std::string name) const;

    private:
        void cleanLine(std::string &str);
        std::string getLineByName(const std::string name) const;
        void commentManagingLine(std::string line);
        void objInline();
        void correctFile();
        std::string getAfterMatch(std::string line, std::string match) const;
        size_t getStartOf(const std::string &line, size_t pos) const;
        std::pair<size_t, size_t> getOnceBlock(std::string &line) const;
        std::vector<std::string> getParseFile(const std::string &line) const;

    protected:
    private:
        std::vector<std::string> _fileContent;
};

#endif /* !CONFIGFILE_HPP_ */
