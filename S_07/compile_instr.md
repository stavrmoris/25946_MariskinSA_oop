# Классная работа 7.I–7.II

## macOS

Из папки `S_07/Task_02`

```sh
cmake -S . -B build -DBUILD_TESTS=ON
cmake --build build
./build/robot_app
ctest --test-dir build --output-on-failure
./build/tests/robot_tests
```

## Windows

В Developer PowerShell for VS, из папки `S_07/Task_02`

```powershell
chcp 65001
[Console]::OutputEncoding = [System.Text.UTF8Encoding]::new()
cmake -S . -B build-windows -G "NMake Makefiles" -DBUILD_TESTS=ON
cmake --build build-windows
.\build-windows\robot_app.exe
ctest --test-dir build-windows --output-on-failure
.\build-windows\tests\robot_tests.exe
```

# Домашняя работа 7.III–7.VI

## macOS

Из корня репозитория

```sh
cmake -S S_07/Task_03 -B S_07/Task_03/build
cmake --build S_07/Task_03/build
./S_07/Task_03/build/robot_lifetime
./S_07/Task_03/build/robot_containers

cmake -S S_07/Task_04 -B S_07/Task_04/build
cmake --build S_07/Task_04/build
./S_07/Task_04/build/robot_app

cmake -S S_07/Task_05 -B S_07/Task_05/build
cmake --build S_07/Task_05/build
./S_07/Task_05/build/robot_app

cmake -S S_07/Task_06 -B S_07/Task_06/build
cmake --build S_07/Task_06/build
./S_07/Task_06/build/robot_app
./S_07/Task_06/build/robot_lifetime
./S_07/Task_06/build/robot_containers
```

## Windows

В Developer PowerShell for VS, из корня репозитория

```powershell
chcp 65001
[Console]::OutputEncoding = [System.Text.UTF8Encoding]::new()

cmake -S S_07/Task_03 -B S_07/Task_03/build-windows -G "NMake Makefiles"
cmake --build S_07/Task_03/build-windows
.\S_07\Task_03\build-windows\robot_lifetime.exe
.\S_07\Task_03\build-windows\robot_containers.exe

cmake -S S_07/Task_04 -B S_07/Task_04/build-windows -G "NMake Makefiles"
cmake --build S_07/Task_04/build-windows
.\S_07\Task_04\build-windows\robot_app.exe

cmake -S S_07/Task_05 -B S_07/Task_05/build-windows -G "NMake Makefiles"
cmake --build S_07/Task_05/build-windows
.\S_07\Task_05\build-windows\robot_app.exe

cmake -S S_07/Task_06 -B S_07/Task_06/build-windows -G "NMake Makefiles"
cmake --build S_07/Task_06/build-windows
.\S_07\Task_06\build-windows\robot_app.exe
.\S_07\Task_06\build-windows\robot_lifetime.exe
.\S_07\Task_06\build-windows\robot_containers.exe
```

Для 7.IV–7.VI вводите четыре поля: `"Арчи" 80 "идти вперёд" 12.5`
При неправильных данных повторите ввод всей записи
