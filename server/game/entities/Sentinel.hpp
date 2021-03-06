//
// Created by mathi on 13/11/2020.
//

#ifndef RTYPE_COLLECTIBLE_HPP
#define RTYPE_COLLECTIBLE_HPP

#include "ecs/Entity.hpp"
#include "tools/Geometry.hpp"
#include "graphical/ATexture.hpp"
#include "graphical/ASprite.hpp"
#include "components/TransformComponent.hpp"
#include "components/AnimationComponent.hpp"
#include "components/SpriteComponent.hpp"
#include "components/ProjectileComponent.hpp"
#include "components/AutomaticWeaponComponent.hpp"
#include "dataHolders/DataSprite.hpp"

#define SENTINEL_FILE "../../client/assets/images/weapons/sentinel_16x14x12_20x16x6_23x31x4.png"

class Sentinel : public Engine::Entity {
private:
    std::map<int, std::vector<Engine::Box<double>>> _anims{
            {0,{
                       {{16 * 0, 0}, {16, 14}},
                       {{16 * 1, 0}, {16, 14}},
                       {{16 * 2, 0}, {16, 14}},
                       {{16 * 3, 0}, {16, 14}},
                       {{16 * 4, 0}, {16, 14}},
                       {{16 * 5, 0}, {16, 14}},
                       {{16 * 6, 0}, {16, 14}},
                       {{16 * 7, 0}, {16, 14}},
                       {{16 * 8, 0}, {16, 14}},
                       {{16 * 9, 0}, {16, 14}},
                       {{16 * 10, 0}, {16, 14}},
                       {{16 * 11, 0}, {16, 14}}}},
            {1,{
                       {{20 * 0, 14}, {20, 16}},
                       {{20 * 1, 14}, {20, 16}},
                       {{20 * 2, 14}, {20, 16}},
                       {{20 * 3, 14}, {20, 16}},
                       {{20 * 4, 14}, {20, 16}},
                       {{20 * 5, 14}, {20, 16}}}},
            {2,{
                       {{23 * 0, 30}, {23, 31}},
                       {{23 * 1, 30}, {23, 31}},
                       {{23 * 2, 30}, {23, 31}},
                       {{23 * 3, 30}, {23, 31}}}}
    };
public:
    explicit Sentinel(const Engine::Point<double> &pos) : Engine::Entity()
    {
        std::unique_ptr<Engine::ASprite> spr = std::make_unique<DataSprite>(SENTINEL_FILE, _anims[0][0]);

        this->addComponent<Engine::TransformComponent>(pos);
        this->addComponent<Engine::AnimationComponent>(0.1);
        this->addComponent<Engine::SpriteComponent>(10, std::move(spr));
        this->addComponent<AutomaticWeaponComponent>(1.0, 0.5, Engine::Vector<double>{50.0, 0},
                                                     Collision::Mask::PLAYER_PROJECTILE, ProjectileComponent::Type::BEAM);
        this->getComponent<AutomaticWeaponComponent>()->setBounce(false);
        this->getComponent<AutomaticWeaponComponent>()->setUseTargets(false);
        this->getComponent<Engine::AnimationComponent>()->addAnimation(0, _anims[0]);
        this->getComponent<Engine::AnimationComponent>()->addAnimation(1, _anims[1]);
        this->getComponent<Engine::AnimationComponent>()->addAnimation(2, _anims[2]);
        this->getComponent<Engine::AnimationComponent>()->setAnimation(0, true);
    }
};

#endif //RTYPE_COLLECTIBLE_HPP
