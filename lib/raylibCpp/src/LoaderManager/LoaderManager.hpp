/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** LoaderManager
*/

#ifndef LOADERMANAGER_HPP
#define LOADERMANAGER_HPP

#include "ILoaderManager.hpp"
#include <cstring>
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
                std::string toLoad(loadIn);

                if (std::strncmp(toLoad.c_str(), "./", 2) == 0)
                    toLoad = toLoad.substr(2, toLoad.size());
                try {
                    return this->_storage.at(toLoad);
                } catch (const std::out_of_range &e) {
                    (void) e;
                    this->_storage[toLoad] = this->_loadingFunc(toLoad);
                    return this->_storage.at(toLoad);
                }
            }
        
        private:
            std::function<toLoadType (const stringType &)> _loadingFunc;
            std::function<void (toLoadType &)> _unloadingFunc;
            std::unordered_map<stringType, toLoadType> _storage;
    };
};

#endif