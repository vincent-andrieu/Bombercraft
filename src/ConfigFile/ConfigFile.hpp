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
#include <filesystem>

class ConfigFile : public IConfigFile
{
    public:
        ConfigFile();
        ConfigFile(const std::string &filename);
        ConfigFile(std::vector<std::string> tab);
        ~ConfigFile();

        int getInt(const std::string name) const;
        void createDefault(const std::string &filename) const;
        void loadFile(const std::string &filename);
        float getFloat(const std::string name) const;
        std::string getString(const std::string name) const;
        std::pair<int, int> getPaire(const std::string name) const;

        std::vector<int> getTabInt(const std::string name) const;
        std::vector<std::vector<int>> getTabTabInt(const std::string name) const;

        raylib::MyVector2 getMyVector2(const std::string name) const;
        raylib::MyVector3 getMyVector3(const std::string name) const;
        raylib::MyVector4 getMyVector4(const std::string name) const;

    private:
        void cleanLine(std::string &str);
        std::string getLineByName(const std::string name) const;
        void commentManagingLine(std::string line);
        void objInline(char start, char end);
        void correctFile();
        std::string getAfterMatch(std::string line, std::string match) const;
        size_t getStartOf(const std::string &line, size_t pos) const;
        std::pair<size_t, size_t> getOnceBlock(std::string &line) const;
        std::vector<std::string> getParseFile(const std::string &line) const;
        std::vector<std::string> getParseIn(std::string sym, std::string line, bool activate = false) const;

    protected:
    private:
        std::vector<std::string> _fileContent;
        static const std::vector<std::string> _defaultContent;
};

#endif /* !CONFIGFILE_HPP_ */
