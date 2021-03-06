//
// Created by mathi on 12/11/2020.
//

#ifndef RTYPE_COLLISIONMASKS_HPP
#define RTYPE_COLLISIONMASKS_HPP

#include "ecs/Entity.hpp"
#include "components/ColliderComponent.hpp"
#include "tools/Utils.hpp"

namespace Collision {

    enum Mask {
        PLAYER = 0,
        PLAYER_PROJECTILE = 1,
        ENEMY = 2,
        ENEMY_PROJECTILE = 3,
        WALL = 4,
        BONUS = 5
    };

    static std::map<Mask, std::vector<Mask>> ignoranceMap = {
            {PLAYER, {PLAYER_PROJECTILE}},
            {PLAYER_PROJECTILE, {PLAYER, BONUS, ENEMY_PROJECTILE}},
            {ENEMY, {ENEMY_PROJECTILE, WALL, BONUS}},
            {ENEMY_PROJECTILE, {ENEMY, BONUS, PLAYER_PROJECTILE}},
            {BONUS, {ENEMY_PROJECTILE, ENEMY, PLAYER_PROJECTILE, WALL}}
    };

    static bool doCollide(Mask myMask, std::vector<std::shared_ptr<Engine::Entity>> &entities) {
        Engine::ColliderComponent *collider;

        if (!Engine::Utils::isInMap(ignoranceMap, myMask))
            return false;
        for (auto &e : entities) {
            collider = e->getComponent<Engine::ColliderComponent>();
            if (collider && !Engine::Utils::isInVector(ignoranceMap[myMask], static_cast<Mask>(collider->getCollisionMask())))
                return true;
        }
        return false;
    }

    static std::vector<std::shared_ptr<Engine::Entity>> removeIgnored(Mask myMask, const std::vector<std::shared_ptr<Engine::Entity>> &list)
    {
        auto res = list;
        Engine::ColliderComponent *collider;

        if (!Engine::Utils::isInMap(ignoranceMap, myMask))
            return res;
        for (auto &e : list) {
            collider = e->getComponent<Engine::ColliderComponent>();
            if (Engine::Utils::isInVector(ignoranceMap[myMask], static_cast<Mask>(collider->getCollisionMask())))
                Engine::Utils::removeFromVector(res, e);
        }
        return res;
    }
}

#endif //RTYPE_COLLISIONMASKS_HPP
