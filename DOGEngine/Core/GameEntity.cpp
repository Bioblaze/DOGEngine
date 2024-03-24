#include "GameEntity.h"

GameEntity::GameEntity(entt::registry& registry)
    : registry(registry), entity(registry.create()) {}

GameEntity::~GameEntity() {
    registry.destroy(entity);
}

void GameEntity::setPosition(float x, float y, float z) {
    posX = x;
    posY = y;
    posZ = z;
}

std::tuple<float, float, float> GameEntity::getPosition() const {
    return { posX, posY, posZ };
}
