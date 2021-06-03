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

ConfigFile::ConfigFile(std::vector<std::string> tab)
{
    std::regex isAscii ("^[\\x00-\\x7F]+$");

    this->_fileContent.clear();
    for (auto line : tab) {
        if (!std::regex_search(line, isAscii) && !line.empty()) {
            throw ParserExceptions("The file doesn't contains only ASCII characters !");
        } else {
            this->commentManagingLine(line);
        }
    }
    this->objInline();
    this->correctFile();
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

    if (line.empty())
        throw ParserExceptions("No variable with name: " + name);
    if (!std::regex_search(line, regexp))
        throw ParserExceptions("Incorrect line format for INT: " + line);
    return std::stoi(this->getAfterMatch(line, ": "));
}

float ConfigFile::getFloat(const std::string name) const
{
    std::string line = getLineByName(name);
    std::regex regexp("\"[a-zA-Z]+\": (-)?\\d*(.)\\d$");

    if (line.empty())
        throw ParserExceptions("No variable with name: " + name);
    if (!std::regex_search(line, regexp))
        throw ParserExceptions("Incorrect line format for FLOAT: " + line);
    return std::stof(this->getAfterMatch(line, ": "));
}

std::pair<int, int> ConfigFile::getPaire(const std::string name) const
{
    std::string input;
    std::string line = getLineByName(name);
    std::regex regexp("\"[a-zA-Z]+\": \\{.*\\}$");

    if (line.empty())
        throw ParserExceptions("No variable with name: " + name);
    if (!std::regex_search(line, regexp))
        throw ParserExceptions("Incorrect line format for PAIR: " + line);
    input = this->getAfterMatch(line, ": {");
    input.pop_back();
    ConfigFile inside(this->getParseFile(input));
    return std::pair<int, int>(inside.getInt("x"), inside.getInt("y"));
}

std::string ConfigFile::getString(const std::string name) const
{
    std::string value;
    std::string line = getLineByName(name);
    std::regex regexp("\"[a-zA-Z]+\": \".*\"$");

    if (line.empty())
        throw ParserExceptions("No variable with name: " + name);
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

size_t ConfigFile::getStartOf(const std::string &line, size_t pos) const
{
    size_t cnt = 0;

    for (; pos >= 0; pos--) {
        if (line[pos] == '"')
            cnt++;
        if (cnt == 2)
            return pos;
        if (pos == 0)
            break;
    }    
    throw ParserExceptions("Invalide '\"': symbole not found");
}

std::pair<size_t, size_t> ConfigFile::getOnceBlock(std::string &line) const
{
    size_t first = line.find_first_of(": ");
    size_t second = (line.substr(first + 2, line.length())).find_first_of(": ");
    size_t first_end = 0;
    size_t second_end = 0;

    if (first == std::string::npos)
        throw ParserExceptions("Invalide ': ': symbole not found");
    if (second == std::string::npos)
        return std::pair<size_t, size_t>(0, line.length());
    second += first + 2;
    first_end = getStartOf(line, first);
    second_end = getStartOf(line, second);
    if (second_end < first)
        throw ParserExceptions("Invalide symbole");
    return std::pair<size_t, size_t>(first_end, second_end);
}

std::vector<std::string> ConfigFile::getParseFile(const std::string &line) const
{
    std::string onceStr;
    std::string toWork(line);
    std::pair<size_t, size_t> once;
    std::vector<std::string> parse;

    while (toWork.length()) {
        once = getOnceBlock(toWork);
        onceStr = toWork.substr(once.first, once.second);
        toWork = toWork.substr(once.second, toWork.length());
        parse.push_back(onceStr);
    }
    return parse;
}