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
    this->_fileContent.clear();
}

std::string ConfigFile::getLineByName(const std::string name) const
{
    const std::string startLine("\"" + name + "\": ");
    
    for (auto it = std::begin(_fileContent); it != std::end(_fileContent); ++it) {
        if ((*it).compare(0, startLine.size(), startLine) == 0)
            return (*it);
    }
    return std::string("");
}

void ConfigFile::loadFile(const std::string &filename)
{
    std::string line;
    std::ifstream myfile (filename);
    std::regex isAscii ("^[\\x00-\\x7F]+$");

    if (myfile.is_open()) {
        this->_fileContent.clear();
        while (getline(myfile, line)) {
            if (!std::regex_search(line, isAscii) && !line.empty()) {
                throw ParserExceptions("The file doesn't contains only ASCII characters !");
            } else {
                this->commentManagingLine(line);
            }
        }
        this->objInline();
        this->correctFile();
    } else {
        throw std::invalid_argument("File close");
    }
}

int ConfigFile::getInt(const std::string name) const
{
    std::string line = getLineByName(name);
    std::regex regexp("\"[a-zA-Z]+\": (-)?\\d*$");

    if (!std::regex_search(line, regexp))
        throw ParserExceptions("Incorrect line format for INT: " + line);
    return std::stoi(this->getAfterMatch(line, ": "));
}

float ConfigFile::getFloat(const std::string name) const
{
    std::string line = getLineByName(name);
    std::regex regexp("\"[a-zA-Z]+\": (-)?\\d*(.)\\d$");

    if (!std::regex_search(line, regexp))
        throw ParserExceptions("Incorrect line format for FLOAT: " + line);
    return std::stof(this->getAfterMatch(line, ": "));
}

std::string ConfigFile::getString(const std::string name) const
{
    std::string value;
    std::string line = getLineByName(name);
    std::regex regexp("\"[a-zA-Z]+\": \".*\"$");

    if (!std::regex_search(line, regexp))
        throw ParserExceptions("Incorrect line format for STRING: " + line);
    value = this->getAfterMatch(line, ": \"");
    value.pop_back();
    return value;
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

void ConfigFile::objInline()
{
    std::vector<std::string>::iterator next = this->_fileContent.begin();
    bool stat = false;
    size_t cnt = 0;

    for (auto it = this->_fileContent.begin(); it != this->_fileContent.end(); it++) {
        if (it->back() == '{') {
            cnt = 1;
            do {
                next = it + 1;
                if (next == this->_fileContent.end())
                    throw ParserExceptions("The file incorrect: not find }");
                if (next->back() == '{')
                    cnt++;
                stat = next->back() == '}';
                if (stat)
                    cnt--;
                it->append(*next);
                this->_fileContent.erase(next);
            } while (!stat || cnt != 0);
        }
    }
}

void ConfigFile::correctFile()
{
    std::regex regexp("\"[a-zA-Z]+\": .*");

    for (auto it : this->_fileContent) {
        if (!std::regex_search(it, regexp))
            throw ParserExceptions("Incorrect line: " + it);
    }
}

std::string ConfigFile::getAfterMatch(std::string line, std::string match) const
{
    return line.substr(line.find(match) + match.length(), line.length());
}