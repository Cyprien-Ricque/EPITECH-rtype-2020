/*!
 * @file MainMenu.hpp
 * @brief MainMenu prototypes
 * @authors Paul.S
 * @version 1.0
 * @date 14/11/2020
 *
*/

#ifndef RTYPE_MAINMENU_HPP
#define RTYPE_MAINMENU_HPP

#include "SceneType.hpp"
#include "sceneManagement/AScene.hpp"
#include "graphical/AWindow.hpp"
#include "graphical/AEvents.hpp"

#define RTYPE_LOGO_PATH "../../client/assets/images/others/r_type_logo_700x204.png"
#define RTYPE_LOGO_WIDTH 700
#define RTYPE_LOGO_HEIGHT 204
#define RTYPE_LOGO_POSITION_X (1920 / 2 - RTYPE_LOGO_WIDTH / 2)
#define RTYPE_LOGO_POSITION_Y 50

#define START_BUTTON_PATH "../../client/assets/images/buttons/start/start_button_full_684x57.png"
#define START_BUTTON_Y 0
#define START_BUTTON_X_IDLE 0
#define START_BUTTON_X_HOVER 228
#define START_BUTTON_X_CLICKED 456
#define START_BUTTON_HEIGHT 57
#define START_BUTTON_WIDTH 228
#define START_BUTTON_POSITION_X (1920 / 2 - START_BUTTON_WIDTH / 2) //TODO make a window size macro instead of hardcoded 1920 ?
#define START_BUTTON_POSITION_Y 300

#define SETTINGS_BUTTON_PATH "../../client/assets/images/buttons/settings/settings_button_full_1104x57.png"
#define SETTINGS_BUTTON_Y 0
#define SETTINGS_BUTTON_X_IDLE 0
#define SETTINGS_BUTTON_X_HOVER 368
#define SETTINGS_BUTTON_X_CLICKED 736
#define SETTINGS_BUTTON_HEIGHT 57
#define SETTINGS_BUTTON_WIDTH 368
#define SETTINGS_BUTTON_POSITION_X (1920 / 2 - SETTINGS_BUTTON_WIDTH / 2) //TODO make a window size macro instead of hardcoded 1920 ?
#define SETTINGS_BUTTON_POSITION_Y 500

#define HOW_TO_PLAY_BUTTON_PATH "../../client/assets/images/buttons/how_to_play/how_to_play_button_full_1344x57.png"
#define HOW_TO_PLAY_BUTTON_Y 0
#define HOW_TO_PLAY_BUTTON_X_IDLE 0
#define HOW_TO_PLAY_BUTTON_X_HOVER 448
#define HOW_TO_PLAY_BUTTON_X_CLICKED 896
#define HOW_TO_PLAY_BUTTON_HEIGHT 57
#define HOW_TO_PLAY_BUTTON_WIDTH 448
#define HOW_TO_PLAY_BUTTON_POSITION_X (1920 / 2 - HOW_TO_PLAY_BUTTON_WIDTH / 2) //TODO make a window size macro instead of hardcoded 1920 ?
#define HOW_TO_PLAY_BUTTON_POSITION_Y 700

class MainMenu : public Engine::AScene
{
private:
    std::shared_ptr<Engine::AWindow> _window;
    std::shared_ptr<Engine::AEvents> _events;

    void initEntities() final;
    void initSystems() final;

public:
    /*!
     * \brief MainMenu scene constructor
     * \param window window to be stored as reference
     * \param events events manager to be stored as reference
     *
     * Create the "MainMenu" scene
    */
    MainMenu(std::shared_ptr<Engine::AWindow> &window, std::shared_ptr<Engine::AEvents> &events);
    ~MainMenu() = default;
    std::shared_ptr<Engine::AWindow> getWindow() const;
};

void goToLobbyListScene(std::shared_ptr<Engine::AScene> &);
void goToSettingsScene(std::shared_ptr<Engine::AScene>  &);
void goToHowToPlayScene(std::shared_ptr<Engine::AScene>  &);
void quitGame(std::shared_ptr<Engine::AScene>  &);

#endif //RTYPE_MAINMENU_HPP