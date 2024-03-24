#include "DamageComponent.h"

// Constructor definition
DamageComponent::DamageComponent(int dmg, DamageTypeEnum dmgType)
    : damage(dmg), type(dmgType) {}

// GetDamage definition
std::pair<int, DamageTypeEnum> DamageComponent::GetDamage() const {
    return { damage, type };
}

// GetDamageByDistance definition
int DamageComponent::GetDamageByDistance(float distance) const {
    if (distance <= 0) {
        return damage; // Full damage if target is at the source
    }
    else if (distance >= maxDistance) {
        return 0; // No damage if beyond maxDistance
    }
    // Linearly decrease damage based on distance
    float damageFactor = 1 - (distance / maxDistance);
    return static_cast<int>(damage * damageFactor);
}