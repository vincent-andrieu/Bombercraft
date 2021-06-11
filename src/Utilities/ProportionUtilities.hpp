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
    explicit ProportionUtilities(const raylib::MyVector2 &windowSize = Game::CoreData::settings->getMyVector2("WIN_SIZE"))
        : _windowSize(windowSize){};
    ~ProportionUtilities() = default;

    [[nodiscard]] inline raylib::MyVector2 operator()(const raylib::MyVector2 &percent) const
    {
        return this->getProportion(percent);
    };

    [[nodiscard]] inline raylib::MyVector2 operator()(const float &x, const float &y) const
    {
        return this->getProportion(x, y);
    };

    [[nodiscard]] inline raylib::MyVector2 operator()(
        const raylib::MyVector2 &percent, const raylib::MyVector2 &objectSize, const raylib::MyVector2 &percentOffset) const
    {
        return this->getProportion(percent, objectSize, percentOffset);
    };

    [[nodiscard]] inline raylib::MyVector2 getProportion(const raylib::MyVector2 &percent) const
    {
        return raylib::MyVector2(_windowSize * (percent / 100));
    };

    [[nodiscard]] inline raylib::MyVector2 getProportion(const float &x, const float &y) const
    {
        return raylib::MyVector2(_windowSize * (raylib::MyVector2(x, y) / 100));
    };

    [[nodiscard]] inline raylib::MyVector2 getProportion(
        const raylib::MyVector2 &percent, const raylib::MyVector2 &objectSize, const raylib::MyVector2 &percentOffset) const
    {
        return raylib::MyVector2(_windowSize * (percent / 100) - (objectSize * (percentOffset / 100)));
    };

    [[nodiscard]] static inline raylib::MyVector2 getProportion(
        const raylib::MyVector2 &windowSize, const raylib::MyVector2 &percent)
    {
        return raylib::MyVector2(windowSize * (percent / 100));
    };

    [[nodiscard]] static inline raylib::MyVector2 getProportion(const raylib::MyVector2 &windowSize,
        const raylib::MyVector2 &percent,
        const raylib::MyVector2 &objectSize,
        const raylib::MyVector2 &percentOffset)
    {
        return raylib::MyVector2(windowSize * (percent / 100) - (objectSize * (percentOffset / 100)));
    };

  private:
    raylib::MyVector2 _windowSize;
};

#endif // MY_CPP_CANEVA_PROPORTIONUTILITIES_HPP