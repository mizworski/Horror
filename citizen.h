#include <iostream>
#include <cassert>

#ifndef HORROR_CITIZEN_H
#define HORROR_CITIZEN_H

template <typename T, int lower, int upper>
class Citizen {
private:
    T health;
    T age;
public:
    Citizen(T health, T age) : health(health), age(age) { assert(age >= lower && age <= upper); }
    T getHealth() { return health; }
    T getAge() { return age; }
    void getDamage(T damage) { age = std::max(0, age - damage); }
};

template <typename T>
class Adult : public Citizen<T, 18, 100> {
    using Citizen<T, 18, 100>::Citizen;

};

template <typename T>
class Teenager : public Citizen<T, 11, 17> {
public:
    using Citizen<T, 11, 17>::Citizen;
};

template <typename T>
class Sheriff : public Citizen<T, 18, 100> {
private:
    T attackPower;
public:
    T getAttackPower() { return attackPower; }
    Sheriff(T health, T age, T attackPower) : Citizen<T, 18, 100>::Citizen(health, age), attackPower(attackPower) {};
};


#endif //HORROR_CITIZEN_H
