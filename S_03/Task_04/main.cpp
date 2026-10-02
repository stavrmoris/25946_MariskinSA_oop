#include "containers.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <random>
#include <sstream>
#include <string>
#include <type_traits>
#include <vector>

namespace {
template <typename Value>
std::string format_value(const Value& value)
{
    std::ostringstream output;
    if constexpr (std::is_floating_point_v<Value>) {
        // сохраняем достаточно цифр для точного представления исходного числа
        output << std::setprecision(std::numeric_limits<Value>::max_digits10);
    }
    output << value;
    return output.str();
}

template <typename Container>
std::string value_at(const Container& values, std::size_t index)
{
    auto it = values.begin();
    // доходим до элемента по позиции через итератор, чтобы поддержать и list
    std::advance(it, static_cast<typename std::iterator_traits<decltype(it)>::difference_type>(index));
    return format_value(*it);
}

template <typename Value, std::size_t Size>
std::string value_at(const std::array<Value, Size>& values, std::size_t index)
{
    return format_value(values[index]);
}

std::vector<std::string> make_table_lines(
    const task_04::Inputs& array_values,
    const std::vector<task_04::T1>& vector_values,
    const std::list<task_04::T1>& list_values,
    const std::deque<task_04::T1>& deque_values,
    const task_04::VectorResults& array_result,
    const task_04::ListResults& vector_result,
    const task_04::DequeResults& list_result,
    const task_04::ArrayResults& deque_result)
{
    std::vector<std::string> rows{
        "| Исходные значения array | Результаты в vector | Исходные значения vector | Результаты в list | Исходные значения list | Результаты в deque | Исходные значения deque | Результаты в array |",
        "| ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: |"
    };

    // по условию все строки данных таблицы создаются одним циклом for
    for (std::size_t i = 0; i < task_04::M; ++i) {
        std::ostringstream row;
        row << "| " << value_at(array_values, i)
            << " | " << value_at(array_result, i)
            << " | " << value_at(vector_values, i)
            << " | " << value_at(vector_result, i)
            << " | " << value_at(list_values, i)
            << " | " << value_at(list_result, i)
            << " | " << value_at(deque_values, i)
            << " | " << value_at(deque_result, i) << " |";
        rows.push_back(row.str());
    }
    return rows;
}
}

int main()
{
    std::mt19937 engine(std::random_device{}());
    // один случайный второй аргумент используется во всех вызовах функции
    const task_04::T1 shared_argument = task_04::random_value<task_04::T1>(engine);

    const auto array_values = task_04::make_array(engine);
    const auto vector_values = task_04::make_vector(engine);
    const auto list_values = task_04::make_list(engine);
    const auto deque_values = task_04::make_deque(engine);

    // каждый исходный контейнер обрабатывается отдельно с сохранением порядка элементов
    const auto array_result = task_04::array_to_vector(array_values, shared_argument);
    const auto vector_result = task_04::vector_to_list(vector_values, shared_argument);
    const auto list_result = task_04::list_to_deque(list_values, shared_argument);
    const auto deque_result = task_04::deque_to_array(deque_values, shared_argument);

    const auto rows = make_table_lines(
        array_values, vector_values, list_values, deque_values,
        array_result, vector_result, list_result, deque_result);

    std::ofstream file("results.md");
    if (!file) {
        std::cerr << "Не удалось открыть results.md для записи. Запустите программу из папки задания.\n";
        return 1;
    }

    file << "# Результаты обработки контейнеров\n\n"
         << "Общий второй аргумент для всех контейнеров: `"
         << std::setprecision(std::numeric_limits<task_04::T1>::max_digits10)
         << shared_argument << "`.\n\n";
    for (const auto& row : rows) {
        file << row << '\n';
    }

    std::cout << "Создан файл results.md; строк данных: " << task_04::M
              << "; общий второй аргумент = " << shared_argument << ".\n";
    return file ? 0 : 1;
}
