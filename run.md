# Запуск Study.Table()

Нужны **Qt 6** (модуль Qt Widgets), **компилятор C++** и (удобно) **Qt Creator**. Проект собирается через **qmake** и `StudyTable.pro`.

## Qt Creator (все ОС)

1. Открыть `StudyTable.pro`.
2. Выбрать kit (Desktop Qt 6.x, компилятор системы).
3. Run (▶).

Рабочая директория при запуске должна быть у корня проекта, чтобы находились файлы в `data/` (так обычно делает Qt Creator при открытии `.pro`).

## Терминал: macOS

```bash
cd /путь/к/OOP-project
mkdir -p build && cd build
qmake ../StudyTable.pro
make -j$(sysctl -n hw.ncpu 2>/dev/null || echo 4)
open StudyTable.app
```

Если `qmake` не находится:

- Homebrew: `export PATH="/opt/homebrew/opt/qt/bin:$PATH"` (Intel: `/usr/local/opt/qt/bin`).
- Официальный Qt: `export PATH="$HOME/Qt/6.x.x/macos/bin:$PATH"` (подставьте версию).

Нужны **Xcode Command Line Tools**: `xcode-select --install`.

## Терминал: Windows

Проще открыть **«Qt 6.x.x (MinGW)»** из меню Пуск — там уже в PATH лежат `qmake` и `mingw32-make`.

```cmd
cd C:\путь\к\OOP-project
mkdir build
cd build
qmake ..\StudyTable.pro -spec win32-g++
mingw32-make
release\StudyTable.exe
```

Для **MSVC** — собирать из «Developer Command Prompt» и использовать `-spec win32-msvc`, затем `nmake`. Если `.exe` не стартует без Creator — из папки с exe: `windeployqt StudyTable.exe`.

## Вход в приложение

| Логин | Пароль |
|-------|--------|
| `admin` | `admin123` |
| `teacher1` | `teach123` |
| `student1` | `stud123` |

## Частые проблемы

| Симптом | Что сделать |
|---------|-------------|
| `qmake: command not found` | Добавить `bin` Qt в `PATH` (см. выше). |
| macOS: ошибка Xcode / `xcrun` | `xcode-select --install`. |
| Windows: не видит qmake | Терминал Qt MinGW или ручной PATH к `...\mingw_64\bin`. |
| Нет данных / пусто | Запускать из корня проекта; проверить наличие `data/*.json`. |

База данных не нужна — всё в JSON в `data/`.
