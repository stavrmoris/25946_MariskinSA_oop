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
    std::ifstream file(path);
    if (!file) {
        throw std::runtime_error("не удалось открыть файл: " + path);
    }

    std::string text((std::istreambuf_iterator<char>(file)),
                     std::istreambuf_iterator<char>());
    if (file.bad()) {
        throw std::runtime_error("ошибка чтения файла: " + path);
    }
    // в исходных файлах числа разделены как пробелами, так и запятыми
    std::replace(text.begin(), text.end(), ',', ' ');
    std::istringstream input(text);
    Numbers values;
    while (input >> std::ws && input.peek() != std::char_traits<char>::eof()) {
        int value = 0;
        // извлечение int также читает запись 89-56 как два числа 89 и -56
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
        // новый ключ получает счётчик 0, после чего увеличиваем его
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
    // начальное значение 0LL задаёт тип суммы long long вместо int
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
    if (values.size() < 10) {
        throw std::runtime_error("для суммы первых 10 элементов нужно хотя бы 10 чисел");
    }
    return std::accumulate(values.begin(), values.begin() + 10, 0LL);
}

inline long long magnitude(int value)
{
    // сначала расширяем тип, чтобы модуль минимального int не вызвал переполнение
    const long long wide_value = value;
    return wide_value < 0 ? -wide_value : wide_value;
}

inline int maximum_by_magnitude(const Numbers& values)
{
    if (values.empty()) {
        throw std::runtime_error("нельзя найти максимум в пустом векторе");
    }
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
        [minimum](const auto& entry) {
            return entry.second >= minimum;
        });
    return result;
}

inline Frequencies common_duplicates_for(
    const Frequencies& first, const Frequencies& second)
{
    Frequencies result;
    for (const auto& entry : second) {
        const auto found = first.find(entry.first);
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
    // отбираем числа, которые одновременно удовлетворяют условиям обоих векторов
    std::copy_if(first.begin(), first.end(), std::inserter(result, result.end()),
        [&second](const auto& entry) {
            const auto found = second.find(entry.first);
            return entry.second > 3 && found != second.end() && found->second >= 2;
        });
    return result;
}
}
