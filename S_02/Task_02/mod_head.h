#pragma once

#include <random>

namespace modified {
template <typename Result, typename Argument>
Result average(const Argument& a, const Argument& b)
{
    // static сохраняет состояние генератора между вызовами функции
    static std::mt19937 generator(std::random_device{}());
    // добавка включается с вероятностью 50 процентов
    static std::bernoulli_distribution add_number(0.5);
    static std::uniform_int_distribution<int> random_number(1, 100);

    double result = (static_cast<double>(a) + static_cast<double>(b)) / 2.0;
    if (add_number(generator)) {
        result += random_number(generator);
    }
    // при целочисленном результате дробная часть отбрасывается
    return static_cast<Result>(result);
}
}
