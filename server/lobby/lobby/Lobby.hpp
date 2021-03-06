/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Emilien
*/

#ifndef RTYPE_LOBBY_HPP
#define RTYPE_LOBBY_HPP

#include <vector>
#include <thread>
#include "networking/UDP/UdpSocketInput.hpp"

class Client;
class Game;
class Server;

class Lobby {
public:
    explicit Lobby(int id, char nbSlots, int port, Server *server);
    ~Lobby();
    void run();

    void join(const std::shared_ptr<Client> &cli);
    void leave(const std::shared_ptr<Client> &cli);

    [[nodiscard]] int getId() const;
    [[nodiscard]] bool isInGame() const;
    [[nodiscard]] char getSlots() const;
    [[nodiscard]] char getNbPlayers() const;
    [[nodiscard]] int getPort() const;
    [[nodiscard]] bool getToRemove() const;
private:
    std::vector<std::shared_ptr<Client>> _players{};
    Server *_server;
    std::thread _thread;
    int _id;
    int _port;
    char _nbSlots;
    bool _gameRunning;
    bool _toRemove;
    std::unique_ptr<Game> _game;
    std::unique_ptr<UdpSocketInput> _udpSocketInput;
};

#endif //RTYPE_LOBBY_HPP
