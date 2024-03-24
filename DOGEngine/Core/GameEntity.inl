// addComponent definition
template<typename T, typename... Args>
T& GameEntity::addComponent(Args&&... args) {
    if (hasComponent<T>()) {
        std::cout << "Attempting to add a component of type " << typeid(T).name()
            << " that already exists. Returning attached component." << std::endl;
        return registry.get<T>(entity);
    }
    else {
        return registry.emplace<T>(entity, std::forward<Args>(args)...);
    }
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
