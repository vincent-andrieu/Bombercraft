/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** Model
*/

#ifndef MODEL_HPP
#define MODEL_HPP

#include "../../include/object.hpp"

#include "IModel.hpp"
#include "../Texture/Texture.hpp"

namespace raylib
{
    class Model : public IModel {
      public:
        Model(const std::string &texturePath, const string &filepath, const MyVector3 position = MyVector3(0, 0, 0),
            const RColor color = RColor::RWHITE);
        ~Model();

        void draw();

        void setPosition(const MyVector3 position);
        const MyVector3 &getPosition() const;
        void setRotation(const MyVector3 rotation);
        void setScale(const float scale);
        void setColor(const RColor color);
        void setPath(const string &path);
        void setTexture(const std::string &texturePath);
        void setLoaderManager();

        MyVector3 getRotation() const;

        [[nodiscard]] string getPath() const;

        static std::shared_ptr<raylib::LoaderManager<RModel, std::tuple<std::string, std::string>, tuple_hash>> _loaderManager;

        static RModel myModelLoad(const std::tuple<std::string, std::string> &str);
        static void myModelUnload(RModel &model);

      private:
        MyVector3 _position;
        MyVector3 _rotation;
        float _scale;
        RColor _color;
        std::vector<Texture2D> _textures;
        std::string _texturePath;
        string _path;
        RModel _model;
    };
}; // namespace raylib

#endif // MODEL_HPP