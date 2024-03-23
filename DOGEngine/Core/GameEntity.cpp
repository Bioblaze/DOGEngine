#include "GameEntity.h"

GameEntity::GameEntity(entt::registry& registry)
    : registry(registry), entity(registry.create()) {}

GameEntity::~GameEntity() {
    registry.destroy(entity);
}
