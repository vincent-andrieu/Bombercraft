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

class ConfigFile : public IConfigFile {
  public:
    ConfigFile() = default;
    ConfigFile(const std::string &filename);
    ConfigFile(const std::vector<std::string> &tab);
    ~ConfigFile();

    void createDefault(const std::string &filename) const;

    void loadFile(const std::string &filename) override;

    [[nodiscard]] int getInt(const std::string &name) const override;
    [[nodiscard]] float getFloat(const std::string &name) const override;
    [[nodiscard]] std::string getString(const std::string &name) const override;
    [[nodiscard]] std::pair<int, int> getPair(const std::string &name) const override;

    [[nodiscard]] std::vector<int> getTabInt(const std::string &name) const override;
    [[nodiscard]] std::vector<std::string> getTabString(const std::string &name) const override;
    [[nodiscard]] std::vector<std::vector<int>> getTabTabInt(const std::string &name) const override;

    [[nodiscard]] raylib::MyVector2 getMyVector2(const std::string &name) const override;
    [[nodiscard]] raylib::MyVector3 getMyVector3(const std::string &name) const override;
    [[nodiscard]] raylib::MyVector4 getMyVector4(const std::string &name) const override;

    [[nodiscard]] bool isSetInFile(const std::string &name) const override;

  private:
    void cleanLine(std::string &str);
    [[nodiscard]] std::string getLineByName(const std::string &name) const;
    void commentManagingLine(std::string line);
    void objInline(char start, char end);
    void correctFile();
    [[nodiscard]] static std::string getAfterMatch(const std::string &line, const std::string &match);
    [[nodiscard]] static size_t getStartOf(const std::string &line, size_t pos);
    [[nodiscard]] static std::pair<size_t, size_t> getOnceBlock(std::string &line);
    [[nodiscard]] static std::vector<std::string> getParseFile(const std::string &line);
    [[nodiscard]] static std::vector<std::string> getParseIn(const std::string &sym, std::string line, bool activate = false);

    std::vector<std::string> _fileContent;
    static const std::vector<std::string> _defaultContent;
};

#endif /* !CONFIGFILE_HPP_ */