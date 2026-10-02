#pragma once

namespace original {
template <typename Result, typename Argument>
Result average(const Argument& a, const Argument& b)
{
    // преобразуем до сложения, чтобы вычислить среднее с дробной частью
    const double mean = (static_cast<double>(a) + static_cast<double>(b)) / 2.0;
    return static_cast<Result>(mean);
}
}

namespace by_reference {
template <typename T>
T average(T& a, const T& b)
{
    // ссылка позволяет изменить первый аргумент у вызывающего кода
    a = static_cast<T>((static_cast<double>(a) + static_cast<double>(b)) / 2.0);
    return a;
}
}
