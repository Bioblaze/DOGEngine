#ifndef GAMEENTITY_H
#define GAMEENTITY_H

#include <entt/entt.hpp>

class GameEntity {
public:
    // Constructor
    GameEntity(entt::registry& registry);
    // Destructor
    virtual ~GameEntity();

    // Adds a component of type T to the entity or replaces it if it already exists
    template<typename T, typename... Args>
    T& addComponent(Args&&... args);

    // Removes a component of type T from the entity
    template<typename T>
    void removeComponent();

    // Checks if the entity has a component of type T
    template<typename T>
    bool hasComponent() const;

private:
    entt::registry& registry;
    entt::entity entity;
};

#include <iostream> // For std::cout
#include <string> // For component type name logging (optional)
#include "GameEntity.inl"

#endif // GAMEENTITY_H
