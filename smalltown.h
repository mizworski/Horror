#ifndef HORROR_SMALLTOWN_H
#define HORROR_SMALLTOWN_H

#include <vector>
#include <tuple>
#include <cmath>
#include <algorithm>
#include <array>

#include "monster.h"
#include "citizen.h"

template<typename U>
constexpr int log2(U n) {
    return n < 2 ? 1 : 1 + log2(n / 2);
}

template<typename U>
constexpr int fibosInRange(U upperBound) {
    return 2 * log2(upperBound) + 2;
}

template<typename T, T N>
struct Fibonacci {
    constexpr Fibonacci() : fibs() {
        fibs[0] = 0;
        fibs[1] = 1;
        for (auto i = 2; i < N; ++i) {
            fibs[i] = fibs[i - 1] + fibs[i - 2];
        }
    }

    T fibs[N];
};

constexpr size_t fun(int bound) {
    return 10;
}

template<typename M, typename U, U t0, U t1, typename... C>
class SmallTown {
private:
    M monster_;
    U actTime_;
    U endTime_;
    std::tuple<C...> citizens_;
    size_t aliveCitizensAmount_ = 0;

    static constexpr auto fibonacci() {
        constexpr auto fibonacci = Fibonacci<U, fibosInRange(t1)>();
        return fibonacci;
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
//            if (std::binary_search(fibs().begin(), fibs().end(), actTime_)) {
//                attackAll();
//            }
        }

        actTime_ += timeStep;
        actTime_ %= endTime_ + 1;
    };
};

#endif //HORROR_SMALLTOWN_H
