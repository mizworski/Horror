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

template<class F, class... Ts, std::size_t... Is>
void for_each(const std::tuple<Ts...> &tuple, F func, std::index_sequence<Is...>) {
    using expander = int[];
    (void) expander {0, ((void) func(std::get<Is>(tuple)), 0)...};
}

template<class F, class...Ts>
void for_each(const std::tuple<Ts...> &tuple, F func) {
    for_each(tuple, func, std::make_index_sequence<sizeof...(Ts)>());
}

template<typename M, typename U, U t0, U t1, typename... C>
class SmallTown {
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

    std::vector<U> fibs;

    void attackAll() {
        for_each(citizens_, [=](auto citizen) { //todo taking copy of each citizen, every time hp resets to full
            if (citizen.getHealth() > 0) {
                attack(monster_, citizen);
                if (citizen.getHealth() <= 0) {
                    --aliveCitizensAmount_;
                }
            }
        });
    }

public:
    SmallTown(M monster, C... citizens) : monster_{monster}, citizens_{citizens...}, actTime_{t0}, endTime_{t1} {
        aliveCitizensAmount_ = std::tuple_size<decltype(citizens_)>::value;
        fibs.reserve(fibosInRange(t1));
        for (auto el : fibonacci().fibs) {
            fibs.push_back(el);
        }
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
        } else if (std::binary_search(fibs.begin(), fibs.end(), actTime_)) {
            attackAll();
        }

        actTime_ += timeStep;
        actTime_ %= endTime_ + 1;
    };
};

#endif //HORROR_SMALLTOWN_H
