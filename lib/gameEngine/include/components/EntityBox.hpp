/*
** EPITECH PROJECT, 2021
** indiestudio
** File description:
** EntityBox
*/

#ifndef ENTITYBOX_HPP_
#define ENTITYBOX_HPP_

#include "Component/Component.hpp"
#include "entity.hpp"

namespace Engine
{
    struct EntityBox : public Component<EntityBox> {
        EntityBox(Entity entity) : entity(entity)
        {
        }

        Entity entity;
    };
}

class EntityBox {
    public:
        EntityBox();
        ~EntityBox();

    protected:
    private:
};

#endif /* !ENTITYBOX_HPP_ */
