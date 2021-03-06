//
// Created by mathi on 29/10/2020.
//

#include "graphical/AWindow.hpp"

Engine::AWindow::AWindow(const std::string &title, const Size<double> &windowSize)
: _title(title), _size(windowSize) {}

void Engine::AWindow::setSize(const Size<double> &size)
{
    this->_size = size;
}

void Engine::AWindow::setTitle(const std::string &title)
{
    this->_title = title;
}

Engine::Size<double> Engine::AWindow::getSize() const
{
    return this->_size;
}

std::string Engine::AWindow::getTitle() const
{
    return this->_title;
}

int Engine::AWindow::getFrameRate() const
{
    return _frameRate;
}

bool Engine::AWindow::getVsync() const
{
    return _vSyncEnabled;
}

bool Engine::AWindow::hasSound() const {
    return _sound;
}

void Engine::AWindow::setSound(bool sound) {
    _sound = sound;
}

bool Engine::AWindow::hasMusic() const {
    return _music;
}

void Engine::AWindow::setMusic(bool music) {
    _music = music;
}
