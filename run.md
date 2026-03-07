# 🚀 Запуск Study.Table() — Инструкция для macOS и Windows

> Приложение написано на **C++17** с использованием **Qt 6 (Widgets)**.  
> Для сборки и запуска нужен **Qt Framework** и **компилятор C++**.

---

## 📋 Предварительные требования

| Компонент | macOS | Windows |
|-----------|-------|---------|
| **Qt 6** | Установить через [qt.io](https://www.qt.io/download) или `brew install qt` | Установить через [qt.io](https://www.qt.io/download) |
| **Компилятор C++** | Xcode Command Line Tools (clang) | MinGW (идёт с Qt) или MSVC |
| **Git** | `brew install git` или [git-scm.com](https://git-scm.com/) | [git-scm.com](https://git-scm.com/) |
| **Qt Creator** (опционально) | Входит в установку Qt | Входит в установку Qt |

---

## 🍎 macOS

### Установка зависимостей

#### Вариант A — через Homebrew (рекомендуется)

```bash
# 1. Установить Homebrew (если ещё нет)
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# 2. Установить Qt 6
brew install qt

# 3. Установить Xcode Command Line Tools (компилятор)
xcode-select --install
```

#### Вариант B — через официальный установщик Qt

1. Перейти на [qt.io/download](https://www.qt.io/download)
2. Скачать **Qt Online Installer**
3. Установить **Qt 6.x** с компонентом **Desktop** (macOS)
4. Также установить **Qt Creator** (IDE)

### Сборка и запуск

#### Способ 1: Через Qt Creator (самый простой)

1. Открыть **Qt Creator**
2. `File` → `Open File or Project`
3. Выбрать файл `StudyTable.pro` из папки проекта
4. В диалоге выбрать комплект сборки: **Desktop Qt 6.x.x clang 64bit**
5. Нажать **Configure Project**
6. Нажать зелёный треугольник **▶ Run** (или `Cmd + R`)

#### Способ 2: Через терминал

```bash
# Перейти в папку проекта
cd /path/to/OOP-project

# Создать папку для сборки
mkdir -p build && cd build

# Сгенерировать Makefile
# Если Qt установлен через Homebrew:
/opt/homebrew/opt/qt/bin/qmake ../StudyTable.pro

# Если Qt установлен через официальный установщик:
# ~/Qt/6.x.x/macos/bin/qmake ../StudyTable.pro

# Собрать проект
make -j$(sysctl -n hw.ncpu)

# Запустить приложение
open StudyTable.app
# или
./StudyTable.app/Contents/MacOS/StudyTable
```

> **Совет:** Если `qmake` не найден, добавьте путь к Qt в `PATH`:
> ```bash
> # Для Homebrew:
> export PATH="/opt/homebrew/opt/qt/bin:$PATH"
> 
> # Для официальной установки Qt:
> export PATH="$HOME/Qt/6.x.x/macos/bin:$PATH"
> ```

### Возможные проблемы на macOS

| Проблема | Решение |
|----------|---------|
| `qmake: command not found` | Добавить путь к Qt в `PATH` (см. выше) |
| `xcrun: error: invalid active developer path` | Выполнить `xcode-select --install` |
| Приложение не открывается (Gatekeeper) | `System Settings → Privacy & Security` → разрешить |

---

## 🪟 Windows

### Установка зависимостей

1. Перейти на [qt.io/download](https://www.qt.io/download)
2. Скачать **Qt Online Installer**
3. Запустить установщик и зарегистрироваться (бесплатная лицензия для студентов)
4. Установить следующие компоненты:
   - **Qt 6.x** → **MSVC 2019/2022** или **MinGW 64-bit**
   - **Qt Creator** (IDE)
   - **MinGW 11.x 64-bit** (если выбран MinGW как компилятор)
5. Установить **Git for Windows** с [git-scm.com](https://git-scm.com/)

> **Примечание:** Если вы выбрали **MSVC**, необходимо также установить
> [Visual Studio Build Tools](https://visualstudio.microsoft.com/downloads/)
> или полный **Visual Studio** (Community Edition — бесплатный).

### Сборка и запуск

#### Способ 1: Через Qt Creator (рекомендуется)

1. Открыть **Qt Creator**
2. `File` → `Open File or Project`
3. Выбрать файл `StudyTable.pro` из папки проекта
4. В диалоге выбрать комплект сборки:
   - **Desktop Qt 6.x.x MinGW 64-bit**  или
   - **Desktop Qt 6.x.x MSVC2019 64-bit**
5. Нажать **Configure Project**
6. Нажать зелёный треугольник **▶ Run** (или `Ctrl + R`)

#### Способ 2: Через командную строку (CMD / PowerShell)

```cmd
:: Открыть "Qt MinGW" терминал из меню Пуск
:: Или вручную настроить переменные окружения:

:: Перейти в папку проекта
cd C:\path\to\OOP-project

:: Создать папку для сборки
mkdir build
cd build

:: Сгенерировать Makefile
:: Для MinGW:
qmake ..\StudyTable.pro -spec win32-g++

:: Для MSVC:
:: qmake ..\StudyTable.pro -spec win32-msvc

:: Собрать проект
:: Для MinGW:
mingw32-make

:: Для MSVC:
:: nmake

:: Запустить
release\StudyTable.exe
```

> **Совет:** Проще всего открыть терминал из меню **Пуск → Qt 6.x.x → Qt 6.x.x (MinGW)** — 
> в нём все пути к `qmake`, `g++` и `mingw32-make` уже настроены.

### Возможные проблемы на Windows

| Проблема | Решение |
|----------|---------|
| `qmake не является внутренней командой` | Открыть Qt MinGW терминал или добавить `C:\Qt\6.x.x\mingw_64\bin` в `PATH` |
| `mingw32-make не найден` | Добавить `C:\Qt\Tools\mingw1120_64\bin` в `PATH` |
| Ошибки при сборке MSVC | Открыть **Developer Command Prompt for VS** перед запуском `qmake` |
| Приложение падает при запуске (DLL не найдены) | Скопировать нужные DLL (Qt6Core.dll и др.) рядом с `.exe`, или использовать `windeployqt` (см. ниже) |

#### Развёртывание DLL (если приложение не запускается вне Qt Creator)

```cmd
:: Из папки build\release\
C:\Qt\6.x.x\mingw_64\bin\windeployqt.exe StudyTable.exe
```

Эта команда автоматически скопирует все необходимые DLL-файлы Qt рядом с вашим `.exe`.

---

## 🧪 Тестовые аккаунты

После запуска приложения используйте эти данные для входа:

| Роль | Логин | Пароль |
|------|-------|--------|
| 🔴 Администратор | `admin` | `admin123` |
| 🟡 Преподаватель | `teacher1` | `teach123` |
| 🟢 Студент | `student1` | `stud123` |

---

## 📁 Структура проекта

```
OOP-project/
├── StudyTable.pro        ← Файл проекта (открывать в Qt Creator)
├── main.cpp              ← Точка входа
├── models/               ← Модели данных (User, Course, Grade, Enrollment)
├── views/                ← Qt-окна (Login, Admin, Teacher, Student)
├── controllers/          ← Бизнес-логика
├── database/             ← DatabaseManager (Singleton, работа с JSON)
├── data/                 ← JSON-файлы с данными
└── resources/            ← Стили (main.qss)
```

---

## ❓ FAQ

**Q: Нужна ли база данных (PostgreSQL, MySQL)?**  
A: Нет. Все данные хранятся в JSON-файлах в папке `data/`.

**Q: Можно ли собрать проект без Qt Creator?**  
A: Да, через терминал с помощью `qmake` + `make` (macOS/Linux) или `mingw32-make` (Windows).

**Q: Какая версия Qt нужна?**  
A: Qt 6.x (рекомендуется 6.5 или выше). Qt 5.15 тоже должен работать, но не тестировался.
