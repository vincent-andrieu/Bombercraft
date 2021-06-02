/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** MyVector4
*/

#ifndef MYVECTOR4_HPP
#define MYVECTOR4_HPP

namespace raylib
{
    class MyVector4
    {
        public:
            MyVector4();
            MyVector4(const float a, const float b, const float c, const float d);
            MyVector4(const MyVector4 &src);

        public:
            float a;
            float b;
            float c;
            float d;
    };
    MyVector4 operator+(MyVector4 const &first, MyVector4 const &second);
    MyVector4 operator-(MyVector4 const &first, MyVector4 const &second);
    MyVector4 operator*(MyVector4 const &first, MyVector4 const &second);
    MyVector4 operator/(MyVector4 const &first, MyVector4 const &second);
    bool operator==(MyVector4 const &first, MyVector4 const &second);
};

#endif