/*
** EPITECH PROJECT, 2021
** ProportionUtilities.hpp
** File description:
** Utility to calculate positions and sizes depending on window size
*/
#ifndef MY_CPP_CANEVA_PROPORTIONUTILITIES_HPP
#define MY_CPP_CANEVA_PROPORTIONUTILITIES_HPP

#include "raylib.hpp"

class ProportionUtilities {
  public:
    explicit ProportionUtilities(const raylib::MyVector2 &windowSize) : _windowSize(windowSize){};
    ~ProportionUtilities() = default;

    [[nodiscard]] inline raylib::MyVector2 getProportion(const raylib::MyVector2 &percent) const
    {
        return raylib::MyVector2(_windowSize * (percent / 100));
    };

    [[nodiscard]] inline raylib::MyVector2 getProportion(const raylib::MyVector2 &percent,
        const raylib::MyVector2 &objectSize,
        const raylib::MyVector2 &percentOffset = {50, 50}) const
    {
        return raylib::MyVector2(_windowSize * (percent / 100) - (objectSize * (percentOffset / 100)));
    };

    [[nodiscard]] static inline raylib::MyVector2 getProportionWin(
        const raylib::MyVector2 &windowSize, const raylib::MyVector2 &percent)
    {
        return raylib::MyVector2(windowSize * (percent / 100));
    };

    [[nodiscard]] static inline raylib::MyVector2 getProportionWin(const raylib::MyVector2 &windowSize,
        const raylib::MyVector2 &percent,
        const raylib::MyVector2 &objectSize,
        const raylib::MyVector2 &percentOffset = {50, 50})
    {
        return raylib::MyVector2(windowSize * (percent / 100) - (objectSize * (percentOffset / 100)));
    };

  private:
    raylib::MyVector2 _windowSize;
};

#endif // MY_CPP_CANEVA_PROPORTIONUTILITIES_HPP