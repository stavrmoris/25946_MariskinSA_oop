include(FetchContent) # подключаем модуль получения внешних библиотек
if(POLICY CMP0135) # проверяем поддержку политики для времён изменения распакованных файлов
    cmake_policy(SET CMP0135 NEW) # назначаем распакованным файлам время распаковки
endif() # закрываем проверку поддержки политики
FetchContent_Declare( # начинаем описание зависимости
    googletest # задаём имя зависимости
    URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.tar.gz # указываем архив исходников googletest версии 1 15 2
    URL_HASH SHA256=7b42b4d6ed48810c5362c265a17faebe90dc2373c885e5216439d37927f02926 # проверяем скачанный архив по контрольной сумме sha256
) # закрываем описание зависимости
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE) # принудительно сохраняем в кэше использование динамической crt для googletest на msvc
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE) # принудительно отключаем сборку googlemock через логическую настройку кэша
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE) # принудительно отключаем правила установки googletest в систему
FetchContent_MakeAvailable(googletest) # получаем исходники googletest и подключаем его цели к проекту

add_executable(average_tests average_tests.cpp assertion_demo.cpp) # создаём тестовую программу из файлов обычных и демонстрационных проверок
target_link_libraries(average_tests PRIVATE average GTest::gtest_main) # подключаем нашу библиотеку и готовый main googletest без публикации зависимостей
include(GoogleTest) # подключаем модуль cmake для интеграции googletest с ctest
gtest_discover_tests(average_tests) # настраиваем обнаружение тестов после сборки и регистрацию в ctest
