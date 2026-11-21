Из корня репозитория; Windows — Developer PowerShell for VS

## macOS — классная 12

```sh
cmake -S S_12/Task_01 -B S_12/Task_01/build
cmake --build S_12/Task_01/build
./S_12/Task_01/build/human_app
```

## macOS — ДЗ 12.I–II

```sh
cmake -S S_12/Task_02 -B S_12/Task_02/build
cmake --build S_12/Task_02/build
./S_12/Task_02/build/robot_app
cmake --build S_12/Task_02/build --target docs
open S_12/Task_02/build/docs/html/index.html
```

## Windows — классная 12

```powershell
chcp 65001
[Console]::OutputEncoding = [System.Text.UTF8Encoding]::new()
cmake -S S_12/Task_01 -B S_12/Task_01/build-windows -G "NMake Makefiles"
cmake --build S_12/Task_01/build-windows
.\S_12\Task_01\build-windows\human_app.exe
```

## Windows — ДЗ 12.I–II

```powershell
cmake -S S_12/Task_02 -B S_12/Task_02/build-windows -G "NMake Makefiles"
cmake --build S_12/Task_02/build-windows
.\S_12\Task_02\build-windows\robot_app.exe
cmake --build S_12/Task_02/build-windows --target docs
Start-Process .\S_12\Task_02\build-windows\docs\html\index.html
```

Для цели `docs` нужны Doxygen и Graphviz (`doxygen` и `dot` в PATH)
