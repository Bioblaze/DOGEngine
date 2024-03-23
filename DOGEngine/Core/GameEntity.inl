// addComponent definition
template<typename T, typename... Args>
T& GameEntity::addComponent(Args&&... args) {
    if (hasComponent<T>()) {
        registry.replace<T>(entity, std::forward<Args>(args)...);
    }
    else {
        registry.emplace<T>(entity, std::forward<Args>(args)...);
    }
    return registry.get<T>(entity);
}

// removeComponent definition
template<typename T>
void GameEntity::removeComponent() {
    registry.remove<T>(entity);
}

// hasComponent definition
template<typename T>
bool GameEntity::hasComponent() const {
    return registry.all_of<T>(entity);
}
