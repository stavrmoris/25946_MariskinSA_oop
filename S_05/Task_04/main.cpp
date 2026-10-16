#include "average.h"

#include <exception>
#include <iostream>

int main()
{
    int a = 0;
    int b = 0;
    std::cout << "введите два целых числа: ";

    std::cout << "среднее: " << original::average(a, b) << '\n';
    std::cout << "среднее с возможной случайной добавкой: "
              << modified::average(a, b) << '\n';

    return 0;
}
