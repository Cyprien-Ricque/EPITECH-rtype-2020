//
// Created by mathi on 03/11/2020.
//

#ifndef RTYPE_AENTITYGROUP_HPP
#define RTYPE_AENTITYGROUP_HPP

#include "components/MusicComponent.hpp"
#include "ecs/Entity.hpp"

namespace Engine {

    class AEntityGroup
    {
    protected:
        std::vector<std::shared_ptr<Engine::Entity>> _entities;

    public:
        AEntityGroup();
        ~AEntityGroup();

        virtual void freeze();
        virtual void unFreeze();
        void addEntity(std::shared_ptr<Engine::Entity> &entity);
        void addEntities(const std::vector<std::shared_ptr<Engine::Entity>> &entities);
        [[nodiscard]] std::vector<std::shared_ptr<Engine::Entity>> getEntities() const;

    };

}

#endif //RTYPE_AENTITYGROUP_HPP
