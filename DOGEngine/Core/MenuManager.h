#ifndef MENUMANAGER_H
#define MENUMANAGER_H

// Including necessary libraries
#include <memory>

// Enum class for GameMenu
enum class GameMenu {
    MainMenu,
    StartNewGame,
    LoadGame,
    SaveGame,
    Settings,
    PauseMenu,
    GameOver,
    VictoryScreen,
    Credits
};

// MenuManager class definition
class MenuManager {
public:
    // Deleted copy constructor and assignment operator for singleton implementation
    MenuManager(const MenuManager&) = delete;
    MenuManager& operator=(const MenuManager&) = delete;

    // Static method to get the instance of the singleton
    static MenuManager& getInstance();

    // Method to set the current menu
    void setCurrentMenu(GameMenu menu);

    // Method to get the current menu
    GameMenu getCurrentMenu() const;

private:
    // Private constructor for singleton implementation
    MenuManager();

    // Current game menu
    GameMenu currentMenu;

    // Static instance pointer
    static std::unique_ptr<MenuManager> instance;
};

#endif // MENUMANAGER_H
