#include "analysis.h"

#include <exception>
#include <iostream>
#include <utility>

namespace {
void print_frequencies(const task_02::Frequencies& counts)
{
    if (counts.empty()) {
        std::cout << "подходящих чисел нет\n";
        return;
    }
    for (const task_02::Frequencies::value_type& entry : counts) {
        std::cout << entry.first << ": " << entry.second << '\n';
    }
}

void print_vector_info(const task_02::Numbers& values, const std::string& label)
{
    std::cout << '\n' << label << "\nколичество чисел: " << values.size()
              << "\nчастоты через for (число: количество):\n";
    print_frequencies(task_02::frequencies_for(values));
    std::cout << "частоты через std::for_each (число: количество):\n";
    print_frequencies(task_02::frequencies_algorithm(values));
    std::cout << "сумма через std::accumulate: " << task_02::sum_accumulate(values)
              << "\nсумма через std::for_each: " << task_02::sum_for_each(values) << '\n';
    if (values.size() >= 10) {
        std::cout << "сумма первых 10 элементов: " << task_02::sum_first_ten(values) << '\n';
    } else {
        std::cout << "сумма первых 10 элементов недоступна: в векторе меньше 10 чисел\n";
    }
    if (!values.empty()) {
        std::cout << "значение с максимальным модулем через std::accumulate: "
                  << task_02::maximum_by_magnitude(values) << '\n';
    } else {
        std::cout << "максимум по модулю недоступен: вектор пустой\n";
    }
}

void print_common_duplicates(const task_02::Frequencies& common,
                             const task_02::Frequencies& second)
{
    if (common.empty()) {
        std::cout << "подходящих общих чисел нет\n";
        return;
    }
    std::cout << "число | количество в первом | количество во втором\n";
    for (const task_02::Frequencies::value_type& entry : common) {
        std::cout << entry.first << " | " << entry.second
                  << " | " << second.at(entry.first) << '\n';
    }
}
}

int main(int argc, char* argv[])
{
    if (argc != 1 && argc != 3) {
        std::cerr << "укажите два файла: task_02 файл1 файл2\n";
        return 1;
    }

    try {
        std::string first_path = argc == 3 ? argv[1] : "s04_v1_46_1.txt";
        std::string second_path = argc == 3 ? argv[2] : "s04_v1_46_2.txt";
        task_02::Numbers first = task_02::read_numbers(first_path);
        task_02::Numbers second = task_02::read_numbers(second_path);
        // первым считается больший по количеству элементов вектор
        if (first.size() < second.size()) {
            std::swap(first, second);
            std::swap(first_path, second_path);
        }

        std::cout << "задания 4.I и 4.II\nпервый вектор из файла: " << first_path
                  << "\nвторой вектор из файла: " << second_path << '\n';
        print_vector_info(first, "первый вектор");
        print_vector_info(second, "второй вектор");

        const task_02::Frequencies first_counts = task_02::frequencies_for(first);
        const task_02::Frequencies second_counts = task_02::frequencies_for(second);
        std::cout << "\nчисла второго вектора с частотой 2 и более:\n";
        print_frequencies(task_02::repeated_values(second_counts, 2));
        std::cout << "числа первого вектора с частотой больше 3:\n";
        print_frequencies(task_02::repeated_values(first_counts, 4));

        std::cout << "\nобщие повторяющиеся числа через for:\n";
        print_common_duplicates(
            task_02::common_duplicates_for(first_counts, second_counts), second_counts);
        std::cout << "общие повторяющиеся числа через std::copy_if с лямбдой:\n";
        print_common_duplicates(
            task_02::common_duplicates_algorithm(first_counts, second_counts), second_counts);
    } catch (const std::exception& error) {
        std::cerr << "ошибка: " << error.what() << '\n';
        return 1;
    }
    return 0;
}
