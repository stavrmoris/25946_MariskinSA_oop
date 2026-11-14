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

## macOS — ДЗ 11, роботы и UML

```sh
cmake -S S_11/Task_03 -B S_11/Task_03/build
cmake --build S_11/Task_03/build
./S_11/Task_03/build/robot_app
cmake --build S_11/Task_03/build --target uml
open S_11/Task_03/build/classes.svg
```

## Windows — ДЗ 11, роботы и UML

```powershell
cmake -S S_11/Task_03 -B S_11/Task_03/build-windows -G "NMake Makefiles"
cmake --build S_11/Task_03/build-windows
.\S_11\Task_03\build-windows\robot_app.exe
cmake --build S_11/Task_03/build-windows --target uml
Start-Process .\S_11\Task_03\build-windows\classes.svg
```

Для цели `uml` нужен Graphviz (`dot` в PATH)
