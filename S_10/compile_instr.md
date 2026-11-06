# Классная работа 10.I

## macOS

Из корня репозитория

```sh
cmake -S S_10/Task_01 -B S_10/Task_01/build
cmake --build S_10/Task_01/build
./S_10/Task_01/build/robot_app
```

## Windows

В Developer PowerShell for VS, из корня репозитория

```powershell
chcp 65001
[Console]::OutputEncoding = [System.Text.UTF8Encoding]::new()
cmake -S S_10/Task_01 -B S_10/Task_01/build-windows -G "NMake Makefiles"
cmake --build S_10/Task_01/build-windows
.\S_10\Task_01\build-windows\robot_app.exe
```
