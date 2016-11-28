#include <iostream>
#include <typeinfo>
#include "citizen.h"

#ifndef HORROR_MONSTER_H
#define HORROR_MONSTER_H


template <typename T>
class Monster {
private:
    T health;
    T attackPower;
public:
    bool isAlive() { return health > 0; }
    // TODO valueType in some other way???
    static const char* valueType() { return typeid(T).name(); }
    Monster(T health, T attackPower) : health(health), attackPower(attackPower) {};
    T getHealth() { return health; }
    T getAttackPower() { return attackPower; }
    void takeDamage(T damage) {  health = std::max<T>(0, health - damage); }
};

template <typename T>
class Vampire : public Monster<T> {
    using Monster<T>::Monster;
public:
    // TODO template parameter?
    static const std::string monsterType() { return "Vampire"; }
};

template <typename T>
class Mummy : public Monster<T> {
    using Monster<T>::Monster;
public:
    static const std::string monsterType() { return "Mummy"; }

};

template <typename T>
class Zombie : public Monster<T> {
    using Monster<T>::Monster;
public:
    static const std::string monsterType() { return "Zombie"; }
};

template <typename M, typename U>
void attack(M& monster, U& victim) {
    std::cout << victim.getHealth() << std::endl;
    victim.takeDamage(monster.getAttackPower());
};

/**
 * Sheriff also have an attack power.
 */
template<typename T, typename M> 
void attack(M& monster, Sheriff<T>& victim) {
	victim.takeDamage(monster.getAttackPower());
	monster.takeDamage(victim.getAttackPower());
}

#endif //HORROR_MONSTER_H
