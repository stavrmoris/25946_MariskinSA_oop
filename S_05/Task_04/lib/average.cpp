#include "average.h"

#include <limits>
#include <random>
#include <stdexcept>

namespace original {
    int average(int a, int b)
    {
        return static_cast<int>(
            (static_cast<long long>(a) + b) / 2
        );
    }
}

namespace modified {
    int average(int a, int b)
    {
        static std::mt19937 generator(std::random_device{}());
        static std::bernoulli_distribution add_number(0.5);
        static std::uniform_int_distribution<int> random_number(1, 100);

        const int addition = add_number(generator) ? random_number(generator) : 0;
        const long long result = (static_cast<long long>(a) + b + 2LL * addition) / 2;
        return static_cast<int>(result);
    }
}
