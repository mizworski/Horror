#ifndef HORROR_SMALLTOWN_H
#define HORROR_SMALLTOWN_H

#include <vector>
#include <tuple>
#include <cmath>
#include <algorithm>
#include <array>

#include "monster.h"
#include "citizen.h"


template<typename M, typename U, U t0, U t1, typename... C>
class SmallTown {
private:
    M monster_;
    U actTime_;
    U endTime_;
    std::tuple<C...> citizens_;
    size_t aliveCitizensAmount_ = 0;

    constexpr static size_t fibsInRange(int n) {
        return (size_t) (10 + std::ceil(std::log(n * std::sqrt(5) / 2) / std::log((1 + std::sqrt(5)) / 2)));
    }

    constexpr static auto generateFibs(size_t bound) {
        std::array<U, fibsInRange(t1)> fibs;
        fibs[0] = 0;
        fibs[1] = 1;

        for (int i = 2; i < bound; ++i) {
            fibs[i] = fibs[i - 1] + fibs[i - 2];
        }

        return fibs;
    }

    static const std::array<U, fibsInRange(t1)> &fibs() {
        static std::array<U, fibsInRange(t1)> compileTimeFibs(generateFibs(fibsInRange(t1)));
        return compileTimeFibs;
    };

    void attackAll() {

    }

public:
    SmallTown(M monster, C... citizens) : monster_{monster}, citizens_{citizens...}, actTime_{t0}, endTime_{t1} {
        aliveCitizensAmount_ = 1;
    }

    auto getStatus() {
        return std::make_tuple(monster_.monsterType(), monster_.getHealth(), aliveCitizensAmount_);
    }

    void tick(U timeStep) {
        if (monster_.getHealth() == 0 && aliveCitizensAmount_ == 0) {
            std::cout << "DRAW\n";
        } else if (monster_.getHealth() == 0) {
            std::cout << "CITIZENS WON\n";
        } else if (aliveCitizensAmount_ == 0) {
            std::cout << "MONSTER WON\n";
        } else {
            //if (std::binary_search(fibs().begin(), fibs().end(), actTime_)) {
            //    attackAll();
            //}
        }

        actTime_ += timeStep;
        actTime_ %= endTime_ + 1;
    };
};

#endif //HORROR_SMALLTOWN_H
