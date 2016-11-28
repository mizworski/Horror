#include <cassert>
#include <iostream>
#include <type_traits>

#ifndef HORROR_CITIZEN_H
#define HORROR_CITIZEN_H

template <typename T, int lower, int upper, bool isAttacking>
class Citizen {
private:
    T health;
    T age;
    T attackPower;
public:
    /**
     * Constructor for not attacking citizen (adult, teenager)
     */
    template <typename Q = T, typename = typename std::enable_if_t<!isAttacking, Q> >
    Citizen(T health, T age) : health(health), age(age) { assert(age >= lower && age <= upper); }

    /**
     * Constructor for sheriff.
     */
    template <typename Q = T, typename = typename std::enable_if_t<isAttacking, Q> >
    Citizen(T health, T age, T attackPower) : health(health), age(age), attackPower(attackPower) { assert(age >= lower && age <= upper); };

    T getHealth() { return health; }
    T getAge() { return age; }
    void takeDamage(T damage) { health = std::max<T>(0, health - damage); }

    bool isAlive() { return health > 0; }

    /**
     * Return attack power (enabled only for sheriff).
     */
    template <typename Q = T, typename = typename std::enable_if_t<isAttacking, Q> >
    T getAttackPower()  { return attackPower; }
};

template <typename T>
using Adult = Citizen<T, 18, 100, false>;

template <typename T>
using Teenager = Citizen<T, 11, 17, false>;

template <typename T>
using Sheriff = Citizen<T, 18, 100, true>;


#endif //HORROR_CITIZEN_H
