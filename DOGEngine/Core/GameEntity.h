#ifndef GAMEENTITY_H
#define GAMEENTITY_H

#include <entt/entt.hpp>

class GameEntity {
public:
    // Constructor
    GameEntity(entt::registry& registry, int entityId);
    // Destructor
    virtual ~GameEntity();

    // Position manipulation functions
    void setPosition(float x, float y, float z);
    std::tuple<float, float, float> getPosition() const;

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

    // Position variables
    float posX = 0.0f, posY = 0.0f, posZ = 0.0f;
    int entity_id;
};

#include <iostream> // For std::cout
#include <string> // For component type name logging (optional)
#include "GameEntity.inl"

#endif // GAMEENTITY_H
