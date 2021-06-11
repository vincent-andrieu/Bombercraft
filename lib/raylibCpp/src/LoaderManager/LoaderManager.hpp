/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** LoaderManager
*/

#ifndef LOADERMANAGER_HPP
#define LOADERMANAGER_HPP

#include "ILoaderManager.hpp"
#include <functional>
#include <unordered_map>

namespace raylib
{
    template <typename toLoadType, typename stringType>
    class LoaderManager : public ILoaderManager<toLoadType, stringType>
    {
        public:
            LoaderManager(std::function<toLoadType (const stringType &)> load, std::function<void (toLoadType &)> unload = nullptr) : _loadingFunc(load), _unloadingFunc(unload)
            {
            }

            ~LoaderManager()
            {
                if (this->_unloadingFunc) {
                    for (auto it : this->_storage) {
                        this->_unloadingFunc(it.second);
                    }
                }
                this->_storage.clear();
            }

            const toLoadType &load(const stringType &loadIn)
            {
                try {
                    return this->_storage.at(loadIn);
                } catch (const std::out_of_range &e) {
                    (void) e;
                    this->_storage[loadIn] = this->_loadingFunc(loadIn);
                    return this->_storage.at(loadIn);
                }
            }
        
        private:
            std::function<toLoadType (const stringType &)> _loadingFunc;
            std::function<void (toLoadType &)> _unloadingFunc;
            std::unordered_map<stringType, toLoadType> _storage;
    };
};

#endif