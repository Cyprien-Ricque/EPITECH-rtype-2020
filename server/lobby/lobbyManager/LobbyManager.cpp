/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Emilien
*/

#include "LobbyManager.hpp"
#include "Client.hpp"
#include "TCP/TcpSocket.hpp"

LobbyManager::LobbyManager(Server *server) : _port(4243), _server(server)
{}

Lobby *LobbyManager::addLobby(char nbSlots = 4)
{
    auto lobbyCpy = _lobbys;

    for (int i = 0; i < lobbyCpy.size(); ++i) {
        if (lobbyCpy.at(i)->getToRemove()) {
            delete lobbyCpy.at(i);
            _lobbys.erase(_lobbys.begin() + i);
            i = (i > 0 ? i - 1 : 0);
        }
    }
    try {
        auto *nLobby = new Lobby(this->_id++, nbSlots, _port++, _server);

        this->_lobbys.push_back(nLobby);
        return nLobby;
    } catch (std::bad_alloc &a) {
        std::cerr << "Error Lobby alloc " << a.what() << std::endl;
        return nullptr;
    }
}

std::vector<Lobby *> LobbyManager::getAvailableLobbies() const
{
    std::vector<Lobby *> output;

    for (auto a : this->_lobbys) {
        if (a && !a->isInGame())
            output.push_back(a);
    }
    return output;
}

void LobbyManager::removeClientInLobbies(std::shared_ptr<Client> &cli)
{
    for (auto &a : _lobbys)
        a->leave(cli);
}

Lobby *LobbyManager::getLobbyById(int id)
{
    for (auto &a : this->_lobbys) {
        if (a->getId() == id)
            return (a);
    }
    return nullptr;
}
