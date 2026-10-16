#include "average.h"

#include <exception>
#include <iostream>

int main()
{
    int a = 0;
    int b = 0;
    std::cout << "введите два целых числа: ";
    if (!(std::cin >> a >> b)) {
        std::cerr << "не удалось прочитать два числа\n";
        return 1;
    }
    try {
        std::cout << "среднее: " << original::average<int>(a, b) << '\n';
        std::cout << "среднее с возможной случайной добавкой: "
                  << modified::average<int>(a, b) << '\n';
    } catch (const std::exception& error) {
        std::cerr << "ошибка: " << error.what() << '\n';
        return 1;
    }
    return 0;
}
