/*
** EPITECH PROJECT, 2021
** Tools
** File description:
** Preloader.hpp
*/

#ifndef PRELOADER_HPP
#define PRELOADER_HPP

#include <vector>
#include <functional>

template <typename toLoadType, typename paramType>
class Preloader
{
    public:
        Preloader(std::function<const toLoadType &(const paramType &)> toRun, std::vector<paramType> listToLoad) : _toRun(toRun), _listToLoad(listToLoad), _startSize(listToLoad.size())
        {
        }

        ~Preloader()
        {
        }

        bool isFinish() const
        {
            return !this->_listToLoad.size();
        }

        size_t getPourcentOfRun() const
        {
            if (!this->_startSize)
                return 100;
            return (size_t)(((float) (this->_startSize - this->_listToLoad.size()) / this->_startSize) * 100);
        }

        void nextLoad()
        {
            if (!this->isFinish()) {
                this->_toRun(this->_listToLoad.back());
                this->_listToLoad.pop_back();
            }
        }
    
    private:
        std::function<const toLoadType &(const paramType &loadIn)> _toRun;
        std::vector<paramType> _listToLoad;
        size_t _startSize;
};


#endif