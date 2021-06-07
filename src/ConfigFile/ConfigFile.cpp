/*
** EPITECH PROJECT, 2021
** indiestudio
** File description:
** ConfigFile
*/

#include "ConfigFile.hpp"

const std::vector<std::string> ConfigFile::_defaultContent = {
    "##",
    "## BOMBERMAN",
    "##",
    "",
    "## MAP",
    "",
    "\"BONUS_POURCENT\": 5",
    "\"EMPTY_POURCENT\": 30",
    "\"SOFT__POURCENT\": 65",
    "",
    "\"MAP_CONFIG\": [",
    "    [1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1],",
    "    [1, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 1],",
    "    [3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3],",
    "    [3, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 3],",
    "    [3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3],",
    "    [3, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 3],",
    "    [3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3],",
    "    [3, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 3],",
    "    [3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3],",
    "    [1, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 1],",
    "    [1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1],",
    "]",
    "",
    "## CORE",
    "",
    "\"WIN_SIZE\": {",
    "    \"a\": 800",
    "    \"b\": 600",
    "}",
    "\"WIN_TITLE\": \"BomberBlock\"",
    "\"WIN_BACK\": 22              #RColor::RBLACK",
    "\"CAM_POSITION\": {",
    "    \"a\": 300",
    "    \"b\": 0",
    "    \"c\": 100",
    "}",
    "\"CAM_TARGET\": {",
    "    \"a\": 0",
    "    \"b\": 0",
    "    \"c\": 0",
    "}",
    "\"CAM_UP\": {",
    "    \"a\": 0",
    "    \"b\": 1",
    "    \"c\": 0",
    "}",
    "",
    "## EXEMPLE",
    "",
    "\"VECTOR_TWO\": {",
    "    \"a\": 3",
    "    \"b\": 4",
    "}",
    "",
    "\"VECTOR_THREE\": {",
    "    \"a\": 3",
    "    \"b\": 434",
    "    \"c\": 5",
    "}",
    "",
    "\"VECTOR_FOUR\": {",
    "    \"a\": 3",
    "    \"b\": 4345",
    "    \"c\": 5",
    "    \"d\": 6",
    "}"
};

ConfigFile::ConfigFile()
{
}

ConfigFile::ConfigFile(const std::string &filename)
{
    std::filesystem::path filepath(filename);

    if (std::filesystem::exists(filepath) == false) {
        this->createDefault(filename);
    }
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
    this->objInline('{', '}');
    this->objInline('[', ']');
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

void ConfigFile::createDefault(const std::string &filename) const
{
    std::ofstream configFile(filename);

    for(const auto& line: _defaultContent) {
        configFile << line << std::endl;
    }
    configFile.close();
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
        this->objInline('{', '}');
        this->objInline('[', ']');
        this->correctFile();
    } else {
        throw ParserExceptions("Fail to open file: " + filename);
    }
}

int ConfigFile::getInt(const std::string name) const
{
    int value = 0;
    std::string line = getLineByName(name);
    std::regex regexp("\"[a-zA-Z_]+\": (-)?\\d*$");

    if (line.empty())
        throw ParserExceptions("No variable with name: " + name);
    if (!std::regex_search(line, regexp))
        throw ParserExceptions("Incorrect line format for INT: " + line);
    try {
        value = std::stoi(this->getAfterMatch(line, ": "));
    } catch ([[maybe_unused]]const std::out_of_range &e) {
        throw ParserExceptions("Incorrect value for FLOAT");
    }
    return value;
}

float ConfigFile::getFloat(const std::string name) const
{
    float value = 0;
    std::string line = getLineByName(name);
    std::regex regexp("\"[a-zA-Z_]+\": (-)?\\d*(.)?\\d$");

    if (line.empty())
        throw ParserExceptions("No variable with name: " + name);
    if (!std::regex_search(line, regexp))
        throw ParserExceptions("Incorrect line format for FLOAT: " + line);
    try {
        value = std::stof(this->getAfterMatch(line, ": "));
    } catch ([[maybe_unused]]const std::out_of_range &e) {
        throw ParserExceptions("Incorrect value for FLOAT");
    }
    return value;
}

std::pair<int, int> ConfigFile::getPaire(const std::string name) const
{
    std::string input;
    std::string line = getLineByName(name);
    std::regex regexp("\"[a-zA-Z_]+\": \\{.*\\}$");

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
    std::regex regexp("\"[a-zA-Z_]+\": \".*\"$");

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

void ConfigFile::objInline(char start, char end)
{
    std::vector<std::string>::iterator next = this->_fileContent.begin();
    bool stat = false;
    size_t cnt = 0;

    for (auto it = this->_fileContent.begin(); it != this->_fileContent.end(); it++) {
        if (it->back() == start) {
            cnt = 1;
            do {
                next = it + 1;
                if (next == this->_fileContent.end())
                    throw ParserExceptions("The file incorrect: not find }");
                if (next->back() == start)
                    cnt++;
                stat = next->back() == end;
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
    std::regex regexp("\"[a-zA-Z_]+\": .*$");

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

    while (true) {
        if (line[pos] == '"')
            cnt++;
        if (cnt == 2)
            return pos;
        if (pos == 0)
            break;
        pos--;
    }
    throw ParserExceptions("Invalid '\"': symbol not found");
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

std::vector<std::string> ConfigFile::getParseIn(std::string sym, std::string line, bool activate) const
{
    size_t pos;
    std::string tmp;
    std::vector<std::string> tab;

    while (1) {
        pos = line.find(sym);
        if (pos == std::string::npos)
            break;
        tmp = line.substr(0, pos);
        if (pos + sym.length() >= line.length())
            break;
        line = line.substr(pos + sym.length(), line.length());
        tab.push_back(tmp);
    }
    if (activate) {
        if (line.length())
            tab.push_back(line.substr(0, line.length() - 1));
        for (std::vector<std::string>::iterator it = tab.begin(); it != tab.end(); it++) {
            if (it->c_str()[0] == '[')
                *it = it->substr(1, it->length());
            if (it->c_str()[it->length()] == ']')
                *it = it->substr(0, it->length() - 1);
        }
    } else {
        if (line.length())
            tab.push_back(line);
    }
    return tab;
}

std::vector<int> ConfigFile::getTabInt(const std::string name) const
{
    std::string input;
    std::vector<int> tab;
    std::vector<std::string> parse;
    std::string line = getLineByName(name);
    std::regex regexp("\"[a-zA-Z_]+\": \\[.*\\]$");

    if (line.empty())
        throw ParserExceptions("No variable with name: " + name);
    if (!std::regex_search(line, regexp))
        throw ParserExceptions("Incorrect line format for Tab: " + line);
    input = this->getAfterMatch(line, ": [");
    input.pop_back();
    parse = this->getParseIn(",", input);
    for (auto once : parse) {
        if (std::all_of(once.begin(), once.end(), ::isdigit))
            tab.push_back(std::stoi(once));
    }
    return tab;
}

std::vector<std::vector<int>> ConfigFile::getTabTabInt(const std::string name) const
{
    std::string input;
    std::vector<int> tab;
    std::vector<std::string> tmp;
    std::vector<std::string> parse;
    std::vector<std::vector<int>> array;
    std::string line = getLineByName(name);
    std::regex regexp("\"[a-zA-Z_]+\": \\[.*\\]$");

    if (line.empty())
        throw ParserExceptions("No variable with name: " + name);
    if (!std::regex_search(line, regexp))
        throw ParserExceptions("Incorrect line format for Tab: " + line);
    input = this->getAfterMatch(line, ": [");
    if (input.length())
        input.pop_back();
    if (input.length())
        input.pop_back();
    parse = this->getParseIn("],", input);
    for (auto lines : parse) {
        tab.clear();
        input = std::string(lines.substr(1, lines.length() - 1));
        tmp = this->getParseIn(", ", input, false);
        for (auto once : tmp) {
            try {
                if (std::all_of(once.begin(), once.end(), ::isdigit))
                    tab.push_back(std::stoi(once));
                else if (once.back() == ']')
                    tab.push_back(std::stoi(once));
            } catch ([[maybe_unused]]const std::out_of_range &e) {
                throw ParserExceptions("Incorrect value for TABTAB");
            } catch ([[maybe_unused]]const std::invalid_argument &e) {
                throw ParserExceptions("Incorrect value for TABTAB");
            }
        }
        array.push_back(tab);
    }
    return array;
}

raylib::MyVector2 ConfigFile::getMyVector2(const std::string name) const
{
    std::string input;
    std::string line = getLineByName(name);
    std::regex regexp("\"[a-zA-Z_]+\": \\{.*\\}$");

    if (line.empty())
        throw ParserExceptions("No variable with name: " + name);
    if (!std::regex_search(line, regexp))
        throw ParserExceptions("Incorrect line format for PAIR: " + line);
    input = this->getAfterMatch(line, ": {");
    input.pop_back();
    ConfigFile inside(this->getParseFile(input));
    return raylib::MyVector2(inside.getFloat("a"), inside.getFloat("b"));
}

raylib::MyVector3 ConfigFile::getMyVector3(const std::string name) const
{
    std::string input;
    std::string line = getLineByName(name);
    std::regex regexp("\"[a-zA-Z_]+\": \\{.*\\}$");

    if (line.empty())
        throw ParserExceptions("No variable with name: " + name);
    if (!std::regex_search(line, regexp))
        throw ParserExceptions("Incorrect line format for PAIR: " + line);
    input = this->getAfterMatch(line, ": {");
    input.pop_back();
    ConfigFile inside(this->getParseFile(input));
    return raylib::MyVector3(inside.getFloat("a"), inside.getFloat("b"), inside.getFloat("c"));
}

raylib::MyVector4 ConfigFile::getMyVector4(const std::string name) const
{
    std::string input;
    std::string line = getLineByName(name);
    std::regex regexp("\"[a-zA-Z_]+\": \\{.*\\}$");

    if (line.empty())
        throw ParserExceptions("No variable with name: " + name);
    if (!std::regex_search(line, regexp))
        throw ParserExceptions("Incorrect line format for PAIR: " + line);
    input = this->getAfterMatch(line, ": {");
    input.pop_back();
    ConfigFile inside(this->getParseFile(input));
    return raylib::MyVector4(inside.getFloat("a"), inside.getFloat("b"), inside.getFloat("c"), inside.getFloat("d"));
}
