/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Emilien
*/

#include "Client.hpp"
#include "Game.hpp"
#include "TCP/TcpSocket.hpp"
#include "Lobby.hpp"

Lobby::Lobby(int id, char nbSlots, int port, Server *server) : _id(id), _nbSlots(nbSlots), _gameRunning(false),
 _port(port), _server(server), _toRemove(false)
{
    _udpSocketInput = std::make_unique<UdpSocketInput>(port);
}

void Lobby::run()
{
    std::vector<int> toSend;
    int i = 0;

    for (const auto &a : _players) {
        toSend.clear();
        toSend.push_back(3);
        toSend.push_back(45);
        toSend.push_back(i++);
        a->sendToClientTcp(toSend);
    }
    _game = std::make_unique<Game>(_players, _udpSocketInput);
    _gameRunning = true;
    _thread = std::thread([&] {
        while (_game->isGameRunning()) {
            _game->update();
        }
        for (const auto &a : _players) {
            toSend.clear();
            toSend.push_back(2);
            toSend.push_back(48);
            a->sendToClientTcp(toSend);
        }
    });
}

void Lobby::join(const std::shared_ptr<Client> &cli)
{
    std::vector<int> toSend;
    if (!_players.empty()) {
        for (auto &a : _players) {
            toSend.clear();
            toSend.push_back(4);
            toSend.push_back(49);
            toSend.push_back(a->getId());
            toSend.push_back(_players.at(0)->getId());
            cli->sendToClientTcp(toSend);
            toSend.clear();
            toSend.push_back(4);
            toSend.push_back(49);
            toSend.push_back(cli->getId());
            toSend.push_back(_players.at(0)->getId());
            a->sendToClientTcp(toSend);
        }
    }
    _players.push_back(cli);
    toSend.clear();
    toSend.push_back(4);
    toSend.push_back(49);
    toSend.push_back(cli->getId());
    toSend.push_back(_players.at(0)->getId());
    cli->sendToClientTcp(toSend);
}

void Lobby::leave(const std::shared_ptr<Client>& cli)
{
    std::vector<int> toSend;

    if (_players.empty())
        return;
    for (auto a = _players.begin(); a != _players.end(); ++a) {
        if (cli->getId() == a->get()->getId()) {
            this->_players.erase(a);
            break;
        }
    }
    if (!_players.empty()) {
        for (auto &a : _players) {
            toSend.clear();
            toSend.push_back(4);
            toSend.push_back(50);
            toSend.push_back(cli->getId());
            toSend.push_back(_players.at(0)->getId());
            a->sendToClientTcp(toSend);
        }
    }
    if (_game && _game->isGameRunning())
        _game->removeClientInGame(cli);
    if (_players.empty())
        _toRemove = true;
}

int Lobby::getId() const
{
    return this->_id;
}

bool Lobby::isInGame() const
{
    return this->_gameRunning;
}

char Lobby::getSlots() const
{
    return this->_nbSlots;
}

char Lobby::getNbPlayers() const
{
    return (char)this->_players.size();
}

int Lobby::getPort() const
{
    return _port;
}

Lobby::~Lobby()
{
    std::vector<int> toSend;

    toSend.push_back(3);
    toSend.push_back(46);
    toSend.push_back(_id);
    if (_server)
        _server->sendToAllClients(toSend);
    if (_game && _game->isGameRunning())
        _game->stopTheGame();
    if (_thread.joinable())
        _thread.join();
}

bool Lobby::getToRemove() const
{
    return _toRemove;
}
