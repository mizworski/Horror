#include <cassert>
#include <type_traits>

#ifndef HORROR_CITIZEN_H
#define HORROR_CITIZEN_H

template <typename T, int lower, int upper, bool isAttacking>
class Citizen {
private:
    T health_;
    T age_;
    T attackPower_;
public:
    /**
     * Constructor for not attacking citizen (adult, teenager)
     */
    template <typename Q = T, typename = typename std::enable_if_t<!isAttacking, Q> >
    Citizen(T health, T age) : health_(health), age_(age) { assert(age >= lower && age <= upper); }

    /**
     * Constructor for sheriff.
     */
    template <typename Q = T, typename = typename std::enable_if_t<isAttacking, Q> >
    Citizen(T health, T age, T attackPower) : health_(health), age_(age), attackPower_(attackPower) { assert(age >= lower && age <= upper); };

    T getHealth() { return health_; }
    T getAge() { return age_; }
    void takeDamage(T damage) {  health_ = health_ >= damage ? health_ - damage : 0; }

    bool isAlive() { return health_ > 0; }

    /**
     * Return attack power (enabled only for sheriff).
     */
    template <typename Q = T, typename = typename std::enable_if_t<isAttacking, Q> >
    T getAttackPower()  { return attackPower_; }
};

template <typename T>
using Adult = Citizen<T, 18, 100, false>;

template <typename T>
using Teenager = Citizen<T, 11, 17, false>;

template <typename T>
using Sheriff = Citizen<T, 18, 100, true>;


#endif //HORROR_CITIZEN_H
