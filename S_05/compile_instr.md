## macOS

Открой терминал в `S_05/Task_04` или `S_05/Task_05`

### Сборка, запуск и тесты

```sh
cmake -S . -B build -DBUILD_TESTS=ON
cmake --build build
./build/average_app
ctest --test-dir build --output-on-failure
./build/tests/average_tests
```

### Демонстрационные провалы

```sh
./build/tests/average_tests --gtest_also_run_disabled_tests --gtest_filter="AssertionDemo.*"
```

### Сборка без тестов

```sh
cmake -S . -B build-no-tests -DBUILD_TESTS=OFF
cmake --build build-no-tests
./build-no-tests/average_app
```

## Windows

Открой Developer PowerShell for VS в `S_05\Task_04` или `S_05\Task_05`

### Сборка, запуск и тесты

```powershell
chcp 65001
[Console]::OutputEncoding = [System.Text.UTF8Encoding]::new()
cmake -S . -B build-windows -G "NMake Makefiles" -DBUILD_TESTS=ON
cmake --build build-windows
.\build-windows\average_app.exe
ctest --test-dir build-windows --output-on-failure
.\build-windows\tests\average_tests.exe
```

### Демонстрационные провалы

```powershell
.\build-windows\tests\average_tests.exe --gtest_also_run_disabled_tests --gtest_filter="AssertionDemo.*"
```

### Сборка без тестов

```powershell
cmake -S . -B build-windows-no-tests -G "NMake Makefiles" -DBUILD_TESTS=OFF
cmake --build build-windows-no-tests
.\build-windows-no-tests\average_app.exe
```
