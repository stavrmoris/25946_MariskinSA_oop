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
