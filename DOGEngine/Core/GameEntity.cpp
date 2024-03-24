#include "GameEntity.h"

GameEntity::GameEntity(entt::registry& registry, int entityId)
    : registry(registry), entity(registry.create()), entity_id(entityId) {}

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
