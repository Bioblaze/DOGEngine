#include "GamePlayer.h"

GamePlayer::GamePlayer(entt::registry& registry)
    : GameEntity(registry) // Initialize the base class part of GamePlayer
{
    // Initialization specific to GamePlayer
}

GamePlayer::~GamePlayer() {
    // Cleanup code specific to GamePlayer, if any
}

void GamePlayer::setName(const std::string& name) {
    playerName = name;
}

std::string GamePlayer::getName() const {
    return playerName;
}
