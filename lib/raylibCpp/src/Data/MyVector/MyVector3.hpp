/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** MyVector3
*/

#ifndef MYVECTOR3_HPP
#define MYVECTOR3_HPP

namespace raylib
{
    class MyVector3
    {
        public:
            MyVector3();
            MyVector3(float a, float b, float c);
            MyVector3(const MyVector3 &src);

        public:
            float a;
            float b;
            float c;
    };
    MyVector3 operator+(MyVector3 const &first, MyVector3 const &second);
    MyVector3 operator-(MyVector3 const &first, MyVector3 const &second);
    MyVector3 operator*(MyVector3 const &first, MyVector3 const &second);
    MyVector3 operator/(MyVector3 const &first, MyVector3 const &second);
    bool operator==(MyVector3 const &first, MyVector3 const &second);
};

#endif