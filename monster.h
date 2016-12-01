#include <iostream>
#include <typeinfo>
#include "citizen.h"

#ifndef HORROR_MONSTER_H
#define HORROR_MONSTER_H

enum MonsterType { vampire, mummy, zombie};

template <typename T, MonsterType type>
class Monster {
private:
    T health_;
    T attackPower_;
public:
    Monster(T health, T attackPower) : health_(health), attackPower_(attackPower) {};
    T getHealth() { return health_; }
    T getAttackPower() { return attackPower_; }
    void takeDamage(T damage) {  health_ = health_ >= damage ? health_ - damage : 0; }

    bool isAlive() { return health_ > 0; }

    using valueType = T;

    static const std::string monsterType() {
        switch(type) {
            case vampire:
                return "Vampire";
            case mummy:
                return "Mummy";
            case zombie:
                return "Zombie";
        }
    }

};

template <typename T>
using Vampire = Monster<T, vampire>;

template <typename T>
using Mummy = Monster<T, mummy>;

template <typename T>
using Zombie = Monster<T, zombie>;

/**
 * Perform attack of monster on the citizen.
 */
template <typename M, typename U>
void attack(M& monster, U& victim) {
    victim.takeDamage(monster.getAttackPower());
};

/**
 * Specialization for a victim being a sheriff, as
 * sheriff also have an attack power.
 */
template<typename T, typename M> 
void attack(M& monster, Sheriff<T>& victim) {
	victim.takeDamage(monster.getAttackPower());
	monster.takeDamage(victim.getAttackPower());
}

#endif //HORROR_MONSTER_H
