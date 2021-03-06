//
// Created by mathi on 29/10/2020.
//

#include <memory>
#include "tools/EngineExceptions.hpp"
#include "Core.hpp"
#include "scenes/MainMenu.hpp"
#include "scenes/Settings.hpp"
#include "scenes/HowToPlay.hpp"
#include "scenes/InGame.hpp"
#include "sfml/GraphicalSFML.hpp"
#include "sfml/WindowSFML.hpp"
#include "sfml/EventsSFML.hpp"
#include "scenes/GroupId.hpp"
#include "scenes/Groups.hpp"
#include "scenes/LobbyList.hpp"
#include "scenes/CreateLobby.hpp"
#include "scenes/LobbyWaiting.hpp"

Core::Core(const std::string &ip)
{
    this->_graph = std::make_unique<GraphicalSFML>();
    this->_graph->setWindow(std::make_shared<WindowSFML>(std::string("r-type"), Engine::Size<double>{1920, 1080}));
    this->_graph->setEvents(std::make_shared<EventsSFML>(_graph->getWindow()));
    this->_server = std::make_shared<NetworkAccess>(ip, 4242, 4200); //TODO: Fix IP with server ip
    this->_timer = std::make_unique<Engine::Timer>();
    this->_sceneManager = std::make_unique<Engine::SceneManager>();
}

void Core::setupGroups()
{
    auto p = std::make_shared<ParallaxGroup>();
    std::shared_ptr<Engine::AEntityGroup> music;

    this->_sceneManager->addGroup(GroupId::MENU_PARALLAX, std::dynamic_pointer_cast<Engine::AEntityGroup>(p));
    music = this->_sceneManager->addGroup(GroupId::MENU_MUSIC, std::dynamic_pointer_cast<Engine::AEntityGroup>(std::make_shared<MusicGroup>()));
    this->_sceneManager->setAccessGroup(SceneType::MAIN_MENU, {GroupId::MENU_PARALLAX, GroupId::MENU_MUSIC});
    this->_sceneManager->setAccessGroup(SceneType::SETTINGS, {GroupId::MENU_PARALLAX, GroupId::MENU_MUSIC});
    this->_sceneManager->setAccessGroup(SceneType::HOW_TO_PLAY, {GroupId::MENU_PARALLAX, GroupId::MENU_MUSIC});
    this->_sceneManager->setAccessGroup(SceneType::LOBBY_LIST, {GroupId::MENU_PARALLAX, GroupId::MENU_MUSIC});
    this->_sceneManager->setAccessGroup(SceneType::CREATE_LOBBY, {GroupId::MENU_PARALLAX, GroupId::MENU_MUSIC});
    this->_sceneManager->setAccessGroup(SceneType::LOBBY_WAITING, {GroupId::MENU_PARALLAX, GroupId::MENU_MUSIC});
    music->unFreeze();
}

void Core::initScenes()
{
    this->_sceneManager->addScene(std::move(std::make_unique<MainMenu>(this->_graph->getWindow(), this->_graph->getEvents())));
    this->_sceneManager->addScene(std::move(std::make_unique<Settings>(this->_graph->getWindow(), this->_graph->getEvents())));
    this->_sceneManager->addScene(std::move(std::make_unique<HowToPlay>(this->_graph->getWindow(), this->_graph->getEvents())));
    this->_sceneManager->addScene(std::move(std::make_unique<LobbyList>(this->_graph->getWindow(), this->_graph->getEvents(), this->_server)));
    this->_sceneManager->addScene(std::move(std::make_unique<InGame>(this->_graph->getWindow(), this->_graph->getEvents(), this->_server)));
    this->_sceneManager->addScene(std::move(std::make_unique<CreateLobby>(this->_graph->getWindow(), this->_graph->getEvents(), this->_server)));
    this->_sceneManager->addScene(std::move(std::make_unique<LobbyWaiting>(this->_graph->getWindow(), this->_graph->getEvents(), this->_server)));
    this->setupGroups();
    try {
        this->_sceneManager->switchScene(MAIN_MENU);
    } catch (Engine::EngineException& e) {
        std::cerr << e << std::endl;
    }
}

void Core::start()
{
    this->initScenes();
    _graph->getWindow()->open();
    this->_graph->getWindow()->setFrameRate(30);
    this->_graph->getWindow()->setVsync(true);
    while (_graph->getWindow()->isOpen())
        run();
}

void Core::run()
{
    this->_sceneManager->handleSceneRequests();
    this->_sceneManager->handleTime(this->_timer->deltatime());
    try {
        this->_sceneManager->getCurrent()->update();
    } catch (Engine::EngineException &e) {
        std::cerr << e << std::endl;
    }
    _graph->getEvents()->update();
    _graph->getWindow()->display();
}