#include "GamePlayer.h"

GamePlayer::GamePlayer(entt::registry& registry, uint32_t connectionId)
    : GameEntity(registry, -1), connection_id(connectionId) // Initialize the base class part of GamePlayer
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
