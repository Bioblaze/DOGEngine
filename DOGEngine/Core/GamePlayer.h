#ifndef GAMEPLAYER_H
#define GAMEPLAYER_H

#include "GameEntity.h"

class GamePlayer : public GameEntity {
public:
    // Constructor. Uses GameEntity's constructor to initialize the base part of the object
    GamePlayer(entt::registry& registry, uint32_t connectionId = 0);

    // Destructor
    virtual ~GamePlayer();

    // Additional player-specific functions can be added here

    // Example function to set player name
    void setName(const std::string& name);

    // Example function to get player name
    std::string getName() const;

private:
    std::string playerName;
    uint32_t connection_id; // Assuming enet uses uint32_t for connection IDs
};

#endif // GAMEPLAYER_H
