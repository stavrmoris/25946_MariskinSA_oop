## macOS

Из корня репозитория

```sh
cmake -S S_08/Task_01 -B S_08/Task_01/build -DBUILD_TESTS=ON
cmake --build S_08/Task_01/build
./S_08/Task_01/build/robot_app
ctest --test-dir S_08/Task_01/build --output-on-failure
./S_08/Task_01/build/tests/robot_tests
```

## Windows

В Developer PowerShell for VS, из корня репозитория

```powershell
chcp 65001
[Console]::OutputEncoding = [System.Text.UTF8Encoding]::new()
cmake -S S_08/Task_01 -B S_08/Task_01/build-windows -G "NMake Makefiles" -DBUILD_TESTS=ON
cmake --build S_08/Task_01/build-windows
.\S_08\Task_01\build-windows\robot_app.exe
ctest --test-dir S_08/Task_01/build-windows --output-on-failure
.\S_08\Task_01\build-windows\tests\robot_tests.exe
```
