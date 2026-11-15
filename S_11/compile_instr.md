Из корня репозитория; Windows — Developer PowerShell for VS

## macOS — перегрузки, using, delete

```sh
cmake -S S_11/Task_01 -B S_11/Task_01/build
cmake --build S_11/Task_01/build
./S_11/Task_01/build/human_app
```

## macOS — множественное и виртуальное наследование

```sh
cmake -S S_11/Task_02 -B S_11/Task_02/build
cmake --build S_11/Task_02/build
./S_11/Task_02/build/human_app
```

## Windows — перегрузки, using, delete

```powershell
chcp 65001
[Console]::OutputEncoding = [System.Text.UTF8Encoding]::new()
cmake -S S_11/Task_01 -B S_11/Task_01/build-windows -G "NMake Makefiles"
cmake --build S_11/Task_01/build-windows
.\S_11\Task_01\build-windows\human_app.exe
```

## Windows — множественное и виртуальное наследование

```powershell
cmake -S S_11/Task_02 -B S_11/Task_02/build-windows -G "NMake Makefiles"
cmake --build S_11/Task_02/build-windows
.\S_11\Task_02\build-windows\human_app.exe
```
