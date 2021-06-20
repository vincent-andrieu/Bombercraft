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

struct tuple_hash
{
    template <class T1, class T2>
    std::size_t operator() (const std::tuple<T1,T2> &p) const {
        auto h1 = std::hash<T1>{}(std::get<0>(p));
        auto h2 = std::hash<T2>{}(std::get<1>(p));

        return h1 ^ h2;
    }
};

struct basic_hash
{
    template <class type>
    std::size_t operator() (const type &p) const {
        return std::hash<type>{}(p);
    }
};

namespace raylib
{
    template <typename toLoadType, typename stringType, typename hash = basic_hash>
    class LoaderManager : public ILoaderManager<toLoadType, stringType>
    {
        public:
            LoaderManager(std::function<toLoadType (const stringType &)> load, std::function<void (toLoadType &)> unload = nullptr, std::function<stringType (std::size_t)> unique = nullptr) : _loadingFunc(load), _unloadingFunc(unload)
            {
            }

            ~LoaderManager()
            {
                if (this->_unloadingFunc) {
                    for (auto it : this->_storage) {
                        this->_unloadingFunc(it.second);
                    }
                    for (auto it : this->_unique) {
                        this->_unloadingFunc(it.second);
                    }
                }
                this->_storage.clear();
            }

            const toLoadType &load(const stringType &loadIn, std::string unique = "")
            {
                if (unique.size()) {
                    try {
                        return this->_unique.at(unique);
                    } catch (const std::out_of_range &e) {
                        (void) e;
                        this->_unique[unique] = this->_loadingFunc(loadIn);
                        return this->_unique.at(unique);
                    }
                } else {
                    try {
                        return this->_storage.at(loadIn);
                    } catch (const std::out_of_range &e) {
                        (void) e;
                        this->_storage[loadIn] = this->_loadingFunc(loadIn);
                        return this->_storage.at(loadIn);
                    }
                }
            }
        
        private:
            std::function<toLoadType (const stringType &)> _loadingFunc;
            std::function<void (toLoadType &)> _unloadingFunc;
            std::unordered_map<stringType, toLoadType, hash> _storage;
            std::unordered_map<std::string, toLoadType> _unique;
    };
};

#endif