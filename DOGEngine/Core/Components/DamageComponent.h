#ifndef DAMAGECOMPONENT_H
#define DAMAGECOMPONENT_H

#include <utility> // For std::pair

// DamageTypeEnum definition
enum class DamageTypeEnum {
    Lava,
    Fire,
    Bullet
};

// DamageComponent definition
struct DamageComponent {
    int damage;
    DamageTypeEnum type;
    float maxDistance; // Maximum effective distance for damage

    // Constructor declaration
    DamageComponent(int dmg, DamageTypeEnum dmgType);

    // Method to get the damage and its type
    std::pair<int, DamageTypeEnum> GetDamage() const;

    // Method to get the adjusted damage based on distance
    int GetDamageByDistance(float distance) const;
};

#endif // DAMAGECOMPONENT_H
