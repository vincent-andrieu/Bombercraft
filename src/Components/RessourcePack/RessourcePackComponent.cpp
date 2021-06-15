/*
 * EPITECH PROJECT, 2021
 * RessourcePack
 * File description:
 * RessourcePackComponent.cpp - Created: 15/06/2021
 */

#include "RessourcePackComponent.hpp"

using namespace Component;

RessourcePack::RessourcePack(const string &ressourcePack) : _ressourcePack(ressourcePack)
{
}

void RessourcePack::set(const string &ressourcePack)
{
    this->_ressourcePack = ressourcePack;
}