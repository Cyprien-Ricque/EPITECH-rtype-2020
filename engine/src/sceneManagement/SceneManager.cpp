//
// Created by mathi on 29/10/2020.
//

#include "tools/EngineExceptions.hpp"
#include "sceneManagement/SceneManager.hpp"
#include "tools/Utils.hpp"

Engine::SceneManager::~SceneManager()
{
    this->_scenes.clear();
    this->_groups.clear();
}

void Engine::SceneManager::parseRequest(const Engine::SceneRequest &request)
{
    std::map<int, std::shared_ptr<Engine::AEntityGroup>> prev{};
    try {
        prev = this->getCurrent()->getGroupAccess();
    } catch (Engine::EngineException &e) {
        std::cerr << e << std::endl;
        throw EngineException("SceneManager", "Unable to get current scene");
    }
    std::map<int, std::shared_ptr<AEntityGroup>> now;

    switch (request.type()) {
        case QueryType::SWITCH_SCENE:
            try {
                this->switchScene(request.arguments().first);
                now = this->getCurrent()->getGroupAccess();
            } catch (Engine::EngineException &e) {
                std::cerr << e << std::endl;
                throw EngineException("SceneManager", "Unable to change scene");
            }
            for (auto &grp : now) {
                if (!Utils::isInMap(prev, grp.first))
                    grp.second->unFreeze();
            }
            for (auto &grp : prev) {
                if (!Utils::isInMap(now, grp.first))
                    grp.second->freeze();
            }
            break;
        case QueryType::PUSH_TO_GROUP:
            this->addToGroup(request.arguments().first, request.arguments().second);
            for (auto &s : this->_scenes)
                s.second->onGroupUpdate(request.arguments().first);
            break;
        default:
            break;
    }
}

void Engine::SceneManager::handleSceneRequests()
{
    for (auto &entry : this->_scenes) {
        for (auto &request : entry.second->getRequests()) {
            try {
                this->parseRequest(request);
            } catch (Engine::EngineException &e) {
                std::cerr << e << std::endl;
            }
        }
        entry.second->clearRequests();
    }
}

void Engine::SceneManager::handleTime(double deltatime)
{
    for (auto &entry : this->_scenes)
        entry.second->updateDeltatime(deltatime);
}

// Groups

std::shared_ptr<Engine::AEntityGroup> Engine::SceneManager::addGroup(int id, const std::vector<std::shared_ptr<Engine::Entity>> &entities)
{
    if (!Utils::isInMap(this->_groups, id))
        this->_groups[id] = std::make_shared<Engine::AEntityGroup>();
    if (!entities.empty())
        this->_groups[id]->addEntities(entities);
    return this->_groups[id];
}

std::shared_ptr<Engine::AEntityGroup> Engine::SceneManager::addGroup(int id, std::shared_ptr<Engine::AEntityGroup> group)
{
    if (!Utils::isInMap(this->_groups, id))
        this->_groups[id] = std::move(group);
    return this->_groups[id];
}

void Engine::SceneManager::addToGroup(int id, std::shared_ptr<Engine::Entity> entity)
{
    if (!Utils::isInMap(this->_groups, id))
        this->addGroup(id, {entity});
    else
        this->_groups[id]->addEntity(entity);
}

void Engine::SceneManager::addToGroup(int id, std::vector<std::shared_ptr<Engine::Entity>> &entities)
{
    if (!Utils::isInMap(this->_groups, id))
        this->addGroup(id, entities);
    else
        this->_groups[id]->addEntities(entities);
}

void Engine::SceneManager::setAccessGroup(int scene, int group)
{
    if (Utils::isInMap(this->_scenes, scene) && Utils::isInMap(this->_groups, group))
        this->_scenes[scene]->addGroupAccess(group, this->_groups[group]);
}

void Engine::SceneManager::setAccessGroup(int scene, const std::vector<int> &groups)
{
    for (int group : groups) {
        if (Utils::isInMap(this->_scenes, scene) && Utils::isInMap(this->_groups, group))
            this->_scenes[scene]->addGroupAccess(group, this->_groups[group]);
    }
}

// Scenes

std::unique_ptr<Engine::AScene> &Engine::SceneManager::getCurrent()
{
    if (Utils::isInMap(this->_scenes, this->_current))
        return this->_scenes[this->_current];
    throw Engine::EngineException("SceneManager", "No target scene");
}

void Engine::SceneManager::addScene(std::unique_ptr<Engine::AScene> scene)
{
    if (Utils::isInMap(this->_scenes, scene->getId()))
        std::cerr << "\033[33mScene WARNING : adding an already existing scene id, will overwrite its data (" << scene->getId() <<")\033[0m" << std::endl;
    this->_scenes[scene->getId()] = std::move(scene);
}

void Engine::SceneManager::switchScene(int id)
{
    if (Utils::isInMap(this->_scenes, this->_current))
        this->_scenes[_current]->onExit();
    if (Utils::isInMap(this->_scenes, id)) {
        this->_current = id;
        this->_scenes[id]->onFocus();
    } else
        throw EngineException("Scene Manager", "No such scene of id: " + std::to_string(id));
}