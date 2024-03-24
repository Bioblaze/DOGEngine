#include "HealthComponent.h"

// Constructor definition
HealthComponent::HealthComponent(int initialHealth) : health(initialHealth), dead(false) {}

// acceptDamage function definition
std::pair<int, bool> HealthComponent::acceptDamage(int damageAmount) {
    health -= damageAmount;
    if (health <= 0) {
        health = 0;
        dead = true;
    }
    return { health, dead };
}

// getHealth function definition
int HealthComponent::getHealth() const {
    return health;
}

// isDead function definition
bool HealthComponent::isDead() const {
    return dead;
}
