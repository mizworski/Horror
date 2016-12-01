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
constexpr size_t log2(U n) {
    return n < 2 ? 1 : 1 + log2(n / 2);
}

template<typename U>
constexpr size_t fibosInRange(U upperBound) {
    return 2 * log2(upperBound) + 2;
}

template<typename T, T fibsLowerThanEndLowerBound>
struct Fibonacci {
    constexpr Fibonacci() : fibs() {
        fibs[0] = 1;
        fibs[1] = 2;
        for (auto i = 2; i < fibsLowerThanEndLowerBound; ++i) {
            fibs[i] = fibs[i - 1] + fibs[i - 2];
            if (fibs[i] < fibs[i-1]) {
                for (int k = i; k < fibsLowerThanEndLowerBound; ++k) {
                    fibs[k] = fibs[i-1];
                }
                break;
            }
        }
    }

    T fibs[fibsLowerThanEndLowerBound];
};

template<typename M, typename U, U t0, U t1, typename... C>
class SmallTown {
    static_assert(std::is_integral<U>::value, "The time type must be integral.");
    static_assert(t0 >= 0, "Start time must be non-negative.");
    static_assert(t0 <= t1, "Start time must precede end time.");
private:
    M monster_;
    U actTime_;
    U endTime_;
    std::tuple<C...> citizens_;
    size_t aliveCitizensAmount_;

    static constexpr auto fibonacci() {
        constexpr auto fibonacci = Fibonacci<U, fibosInRange(t1)>();
        return fibonacci;
    };

    template<int i, typename H, typename... Args>
    void attackAll() {
        if (std::get<i>(citizens_).isAlive()) {
            attack(monster_, std::get<i>(citizens_));

            if (!std::get<i>(citizens_).isAlive()) {
                --aliveCitizensAmount_;
            }
        }

        attackAll<i + 1, Args...>();
    }

    template<int i>
    void attackAll() {
    };

    bool isFibonacci(int actTime) {
        for (int i = 0; i < fibosInRange(t1); ++i) {
            if (fibonacci().fibs[i] == actTime) {
                return true;
            }
        }
        return false;
    }

public:
    SmallTown(M monster, C... citizens) : monster_{monster}, actTime_{t0}, endTime_{t1}, citizens_{citizens...} {
        aliveCitizensAmount_ = std::tuple_size<decltype(citizens_)>::value;
    }

    auto getStatus() {
        return std::make_tuple(monster_.monsterType(), monster_.getHealth(), aliveCitizensAmount_);
    }

    void tick(U timeStep) {
        if (monster_.getHealth() == 0 && aliveCitizensAmount_ == 0) {
            std::cout << "DRAW" << std::endl;
        } else if (monster_.getHealth() == 0) {
            std::cout << "CITIZENS WON" << std::endl;
        } else if (aliveCitizensAmount_ == 0) {
            std::cout << "MONSTER WON" << std::endl;
        } else if (isFibonacci(actTime_)) {
            attackAll<0, C...>();
        }

        actTime_ += timeStep;
        actTime_ %= endTime_ + 1;
    };
};

#endif //HORROR_SMALLTOWN_H
