#ifndef GAMEPLAYER_H
#define GAMEPLAYER_H

#include "GameEntity.h"

class GamePlayer : public GameEntity {
public:
    // Constructor. Uses GameEntity's constructor to initialize the base part of the object
    GamePlayer(entt::registry& registry);

    // Destructor
    virtual ~GamePlayer();

    // Additional player-specific functions can be added here

    // Example function to set player name
    void setName(const std::string& name);

    // Example function to get player name
    std::string getName() const;

private:
    std::string playerName;
};

#endif // GAMEPLAYER_H
