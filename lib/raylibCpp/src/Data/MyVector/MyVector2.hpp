/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** MyVector2
*/

#ifndef MYVECTOR2_HPP
#define MYVECTOR2_HPP

namespace raylib
{
    class MyVector2
    {
        public:
            MyVector2();
            MyVector2(float a, float b);
            MyVector2(const MyVector2 &src);

        public:
            float a;
            float b;
    };
    MyVector2 operator+(MyVector2 const &first, MyVector2 const &second);
    MyVector2 operator-(MyVector2 const &first, MyVector2 const &second);
    MyVector2 operator*(MyVector2 const &first, MyVector2 const &second);
    MyVector2 operator/(MyVector2 const &first, MyVector2 const &second);
    bool operator==(MyVector2 const &first, MyVector2 const &second);
};

#endif