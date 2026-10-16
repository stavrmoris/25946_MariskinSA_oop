#pragma once

#include <limits>
#include <random>
#include <stdexcept>
#include <type_traits>

namespace original {
template <typename Result, typename Argument>
Result average(const Argument& a, const Argument& b)
{
    return static_cast<Result>((static_cast<long double>(a) + b) / 2.0L);
}
}

namespace modified {
template <typename Result, typename Argument>
Result average(const Argument& a, const Argument& b)
{
    static std::mt19937 generator(std::random_device{}());
    static std::bernoulli_distribution add_number(0.5);
    static std::uniform_int_distribution<int> random_number(1, 100);

    long double result = (static_cast<long double>(a) + b) / 2.0L;
    if (add_number(generator)) {
        result += random_number(generator);
    }

    if constexpr (std::is_integral_v<Result>) {
        if (result < std::numeric_limits<Result>::lowest() ||
            result > std::numeric_limits<Result>::max()) {
            throw std::overflow_error("результат не помещается в выбранный тип");
        }
    }
    return static_cast<Result>(result);
}
}
