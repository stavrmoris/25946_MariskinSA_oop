## macOS

Из корня репозитория

```sh
cmake -S S_09/Task_01 -B S_09/Task_01/build
cmake --build S_09/Task_01/build
./S_09/Task_01/build/robot_app
```

## Windows

В Developer PowerShell for VS, из корня репозитория

```powershell
chcp 65001
[Console]::OutputEncoding = [System.Text.UTF8Encoding]::new()
cmake -S S_09/Task_01 -B S_09/Task_01/build-windows -G "NMake Makefiles"
cmake --build S_09/Task_01/build-windows
.\S_09\Task_01\build-windows\robot_app.exe
```

# Домашняя работа 9.I–9.III

## macOS

Из корня репозитория

```sh
cmake -S S_09/Task_03 -B S_09/Task_03/build
cmake --build S_09/Task_03/build
./S_09/Task_03/build/robot_app
```

## Windows

В Developer PowerShell for VS, из корня репозитория

```powershell
chcp 65001
[Console]::OutputEncoding = [System.Text.UTF8Encoding]::new()
cmake -S S_09/Task_03 -B S_09/Task_03/build-windows -G "NMake Makefiles"
cmake --build S_09/Task_03/build-windows
.\S_09\Task_03\build-windows\robot_app.exe
```
