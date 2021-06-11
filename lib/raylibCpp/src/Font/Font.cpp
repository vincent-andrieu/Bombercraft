/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** Font
*/

#include "Font.hpp"

std::shared_ptr<raylib::LoaderManager<RFont, std::string>> raylib::Font::_loaderManager = nullptr;

raylib::Font::Font(const string path)
{
    if (!this->_loaderManager)
        this->setLoaderManager();
    this->_path = path;
    if (this->_path.compare("") != 0) {
        this->_font = raylib::Font::_loaderManager->load(this->_path);
        this->_hasFont = true;
    } else {
        this->_font = GetFontDefault();
        this->_hasFont = false;
    }
}

raylib::Font::~Font()
{
}

void raylib::Font::setPath(const string &path)
{
    this->_path = path;
    UnloadFont(this->_font);
    this->_hasFont = true;
    this->_font = raylib::Font::_loaderManager->load(this->_path);
}

RFont raylib::Font::getFont() const
{
    return this->_font;
}

void raylib::Font::reset()
{
    if (this->_hasFont) {
        this->_hasFont = false;
    }
}

void raylib::Font::setLoaderManager()
{
    if (!this->_loaderManager) {
        this->_loaderManager = std::make_shared<raylib::LoaderManager<RFont, std::string>>(raylib::Font::myFontLoad, raylib::Font::myFontUnload);
    } else {
        this->_loaderManager.reset();
        this->_loaderManager = std::make_shared<raylib::LoaderManager<RFont, std::string>>(raylib::Font::myFontLoad, raylib::Font::myFontUnload);
    }
}

RFont raylib::Font::myFontLoad(const std::string &str)
{
    return LoadFont(str.data());
}

void raylib::Font::myFontUnload(RFont &font)
{
    UnloadFont(font);
}