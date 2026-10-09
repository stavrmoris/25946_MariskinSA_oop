#pragma once

#include <algorithm>
#include <fstream>
#include <iterator>
#include <map>
#include <numeric>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace task_02 {
using Numbers = std::vector<int>;
using Frequencies = std::map<int, std::size_t>;

inline Numbers read_numbers(const std::string& path)
{
    std::ifstream file(path); // открываем поток файла

    std::string text((std::istreambuf_iterator<char>(file)), // итератор чтения
                     std::istreambuf_iterator<char>());      // итератор конца потока

    std::replace(text.begin(), text.end(), ',', ' ');
    std::istringstream input(text);
    Numbers values;
    while (input >> std::ws && input.peek() != std::char_traits<char>::eof()) {
        int value = 0;
        // читает запись 89-56 как 2 числа 89 и -56
        if (!(input >> value)) {
            throw std::runtime_error("некорректное число или выход за диапазон int в файле: " + path);
        }
        values.push_back(value);
    }
    return values;
}

inline Frequencies frequencies_for(const Numbers& values)
{
    Frequencies counts;
    for (int value : values) {
        // новый ключ получает 0, после - увеличиваем
        ++counts[value];
    }
    return counts;
}

inline Frequencies frequencies_algorithm(const Numbers& values)
{
    Frequencies counts;
    std::for_each(values.begin(), values.end(), [&counts](int value) {
        ++counts[value];
    });
    return counts;
}

inline long long sum_accumulate(const Numbers& values)
{
    // 0LL задает тип long long вместо int
    return std::accumulate(values.begin(), values.end(), 0LL);
}

inline long long sum_for_each(const Numbers& values)
{
    long long sum = 0;
    std::for_each(values.begin(), values.end(), [&sum](int value) {
        sum += value;
    });
    return sum;
}

inline long long sum_first_ten(const Numbers& values)
{
    return std::accumulate(values.begin(), values.begin() + 10, 0LL);
}

inline long long magnitude(int value)
{
    // расширяем тип, чтобы модуль не вызвал переполнение
    const long long wide_value = value;
    return wide_value < 0 ? -wide_value : wide_value;
}

inline int maximum_by_magnitude(const Numbers& values)
{
    // сохраняем исходный знак, при равных модулях остаётся первое значение
    return std::accumulate(std::next(values.begin()), values.end(), values.front(),
        [](int current, int value) {
            return magnitude(value) > magnitude(current) ? value : current;
        });
}

inline Frequencies repeated_values(const Frequencies& counts, std::size_t minimum)
{
    Frequencies result;
    std::copy_if(counts.begin(), counts.end(), std::inserter(result, result.end()),
        [minimum](const Frequencies::value_type& entry) {
            return entry.second >= minimum;
        });
    return result;
}

inline Frequencies common_duplicates_for(
    const Frequencies& first, const Frequencies& second)
{
    Frequencies result;
    for (const Frequencies::value_type& entry : second) {
        const Frequencies::const_iterator found = first.find(entry.first);
        if (entry.second >= 2 && found != first.end() && found->second > 3) {
            result.emplace(found->first, found->second);
        }
    }
    return result;
}

inline Frequencies common_duplicates_algorithm(
    const Frequencies& first, const Frequencies& second)
{
    Frequencies result;
    std::copy_if(first.begin(), first.end(), std::inserter(result, result.end()),
        [&second](const Frequencies::value_type& entry) {
            const Frequencies::const_iterator found = second.find(entry.first);
            return entry.second > 3 && found != second.end() && found->second >= 2;
        });
    return result;
}
}
