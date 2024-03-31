#include "MenuManager.h"

// Initialize the static instance pointer to nullptr
std::unique_ptr<MenuManager> MenuManager::instance = nullptr;

// Implementation of getInstance method
MenuManager& MenuManager::getInstance() {
    if (!instance) {
        instance = std::unique_ptr<MenuManager>(new MenuManager());
    }
    return *instance;
}

// Private constructor definition
MenuManager::MenuManager() : currentMenu(GameMenu::MainMenu) {
    // Constructor body can initialize other members if necessary
}

// Implementation of setCurrentMenu method
void MenuManager::setCurrentMenu(GameMenu menu) {
    currentMenu = menu;
}

// Implementation of getCurrentMenu method
GameMenu MenuManager::getCurrentMenu() const {
    return currentMenu;
}
