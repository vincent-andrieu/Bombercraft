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
            MyVector4(float a, float b, float c, float d);
            MyVector4(const MyVector4 &src);

        public:
            float a;
            float b;
            float c;
            float d;
    };
};

#endif