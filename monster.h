#include <iostream>
#include <typeinfo>
#include "citizen.h"

#ifndef HORROR_MONSTER_H
#define HORROR_MONSTER_H

enum MonsterType { vampire, mummy, zombie};

template <typename T, MonsterType type>
class Monster {
private:
    T health;
    T attackPower;
public:
    Monster(T health, T attackPower) : health(health), attackPower(attackPower) {};
    T getHealth() { return health; }
    T getAttackPower() { return attackPower; }
    // TODO types casting??
    void takeDamage(T damage) {  health = std::max<T>(0, health - damage); }

    bool isAlive() { return health > 0; }

    // TODO valueType in some other way???
    static const char* valueType() { return typeid(T).name(); }

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
    std::cout << victim.getHealth() << std::endl;
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
