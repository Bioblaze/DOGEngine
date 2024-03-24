#ifndef HEALTHCOMPONENT_H
#define HEALTHCOMPONENT_H

#include <utility> // For std::pair

struct HealthComponent {
    int health;
    bool dead;

    // Constructor declaration
    HealthComponent(int initialHealth);

    // acceptDamage function declaration
    std::pair<int, bool> acceptDamage(int damageAmount);

    // getHealth function declaration
    int getHealth() const;

    // isDead function declaration
    bool isDead() const;
};

#endif // HEALTHCOMPONENT_H
