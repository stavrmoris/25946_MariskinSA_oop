```sh
cd S_05/Task_05
cmake -S . -B build -DBUILD_TESTS=ON
cmake --build build
./build/average_app
ctest --test-dir build --output-on-failure
./build/tests/average_tests
./build/tests/average_tests --gtest_also_run_disabled_tests --gtest_filter="AssertionDemo.*"
cmake -S . -B build-no-tests -DBUILD_TESTS=OFF
cmake --build build-no-tests
./build-no-tests/average_app
```

```powershell
cd S_05\Task_05
chcp 65001
[Console]::OutputEncoding = [System.Text.UTF8Encoding]::new()
cmake -S . -B build -G "NMake Makefiles" -DBUILD_TESTS=ON
cmake --build build
.\build\average_app.exe
ctest --test-dir build --output-on-failure
.\build\tests\average_tests.exe
.\build\tests\average_tests.exe --gtest_also_run_disabled_tests --gtest_filter="AssertionDemo.*"
cmake -S . -B build-no-tests -G "NMake Makefiles" -DBUILD_TESTS=OFF
cmake --build build-no-tests
.\build-no-tests\average_app.exe
```
