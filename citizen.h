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
public:
    bool isAlive() { return health > 0; }
    Citizen(T health, T age) : health(health), age(age) { assert(age >= lower && age <= upper); }
    T getHealth() { return health; }
    T getAge() { return age; }
    void takeDamage(T damage) { health = std::max<T>(0, health - damage); }
};

template <typename T>
using Adult = Citizen<T, 18, 100, false>;

template <typename T>
using Teenager = Citizen<T, 11, 17, false>;

// TODO specialization instead of inheritance
template <typename T>
class Sheriff : public Citizen<T, 18, 100, true> {
private:
    T attackPower;
public:
    T getAttackPower() { return attackPower; }
    Sheriff(T health, T age, T attackPower) : Citizen<T, 18, 100, true>::Citizen(health, age), attackPower(attackPower) {};
};


#endif //HORROR_CITIZEN_H
