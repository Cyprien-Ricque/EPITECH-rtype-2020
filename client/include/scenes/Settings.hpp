/*!
 * @file Settings.hpp
 * @brief Settings scene declaration
 * @authors Paul.S
 * @version 1.0
 * @date 14/11/2020
 *
*/

#ifndef RTYPE_SETTINGS_HPP
#define RTYPE_SETTINGS_HPP

#include "SceneType.hpp"
#include "sceneManagement/AScene.hpp"
#include "graphical/AWindow.hpp"
#include "graphical/AEvents.hpp"
#include "entities/Button.hpp"
#include "SceneEnum.hpp"
#include "entities/Drawable.hpp"
#include "sfml/SpriteSfml.hpp"

enum SettingsSelectorSprite {
    FRAMERATE,
    VSYNC_ENABLED,
    MUSIC_ENABLED,
    SOUND_EFFECTS_ENABLED
};

class Settings : public Engine::AScene
{
    private:
        std::shared_ptr<Engine::AWindow> _window;
        std::shared_ptr<Engine::AEvents> _events;
        std::vector<std::shared_ptr<Engine::Entity>> _settingsEntities;

        void initEntities() final;
        void initSystems() final;
        void createSelector(Engine::Point<double> position,  const std::pair<void (*)(std::shared_ptr<Engine::AScene> &), void (*)(std::shared_ptr<Engine::AScene> &)> &callback, const std::string &path, std::unique_ptr<SpriteSFML> text);
    public:

        /*!
         * \brief Settings scene constructor
         * \param window window to be stored as reference
         * \param events events manager to be stored as reference
         *
         * Create the "Settings" scene
        */
        Settings(std::shared_ptr<Engine::AWindow> &window, std::shared_ptr<Engine::AEvents> &events);
        std::shared_ptr<Engine::AWindow> getWindow() const;
        std::vector<std::shared_ptr<Engine::Entity>> getSettingsEntities() const;
};

void goToMenuScene(std::shared_ptr<Engine::AScene> &);
void changeWindowFrameratePrev(std::shared_ptr<Engine::AScene> &);
void changeWindowFramerateNext(std::shared_ptr<Engine::AScene> &);
void changeWindowVsync(std::shared_ptr<Engine::AScene> &);
void changeAudioEnableMusic(std::shared_ptr<Engine::AScene> &);
void changeAudioEnableSoundEffects(std::shared_ptr<Engine::AScene> &);

#endif //RTYPE_SETTINGS_HPP