/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** Font
*/

#ifndef FONT_HPP
#define FONT_HPP

#include "../../include/object.hpp"

#include "IFont.hpp"
#include "../LoaderManager/LoaderManager.hpp"

namespace raylib
{
    class Font : public IFont {
      public:
        Font(const string path = "");
        ~Font();

        void setPath(const string &path);

        [[nodiscard]] RFont getFont() const;

        void reset();

        static std::shared_ptr<raylib::LoaderManager<RFont, std::string>> _loaderManager;

      private:
        void setLoaderManager();
        static RFont myFontLoad(const std::string &str);
        static void myFontUnload(RFont &font);

      private:
        string _path;
        RFont _font;
        bool _hasFont;
    };
}; // namespace raylib

#endif // FONT_HPP