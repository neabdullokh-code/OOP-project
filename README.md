# 📚 Study.Table() — CRM для образовательного центра

> Десктопное приложение на **C++ / Qt Framework**, демонстрирующее принципы ООП через графический интерфейс.  
> Команда: **5 человек** · Тип: **Курсовой проект по ООП**

---

## 📋 Оглавление

1. [Описание проекта](#-описание-проекта)
2. [Технологии и инструменты](#-технологии-и-инструменты)
3. [Архитектура проекта](#-архитектура-проекта)
4. [Структура файлов и папок](#-структура-файлов-и-папок)
5. [Принципы ООП в проекте](#-принципы-ооп-в-проекте)
6. [Паттерны проектирования](#-паттерны-проектирования)
7. [Роли пользователей](#-роли-пользователей)
8. [Распределение работы по участникам](#-распределение-работы-по-участникам)
9. [Формат данных (JSON)](#-формат-данных-json)
10. [Как собрать и запустить проект](#-как-собрать-и-запустить-проект)
11. [Git-воркфлоу команды](#-git-воркфлоу-команды)
12. [Аккаунты для тестирования](#-аккаунты-для-тестирования)
13. [Правила и договорённости](#-правила-и-договорённости)

---

## 🎯 Описание проекта

**Study.Table()** — это CRM-система для образовательных центров.  
Приложение позволяет управлять курсами, преподавателями и студентами через удобный графический интерфейс.

### Что умеет приложение

- **Авторизация** — вход по логину и паролю с проверкой роли
- **Панель администратора** — создание/редактирование курсов, управление пользователями
- **Панель преподавателя** — просмотр своих классов, выставление оценок
- **Панель студента** — просмотр записанных курсов и оценок
- **Хранение данных** — все данные сохраняются в JSON-файлах (без базы данных)

---

## 🛠 Технологии и инструменты

| Что | Зачем |
|-----|-------|
| **C++17** | Основной язык программирования |
| **Qt 6 (Widgets)** | Фреймворк для GUI (графический интерфейс) |
| **qmake / CMake** | Система сборки проекта |
| **JSON (QJsonDocument)** | Формат хранения данных (файлы `.json`) |
| **Git + GitHub** | Контроль версий и совместная работа |

### Что нужно установить

1. **Qt Creator** (версия 6.x) — скачать с [qt.io](https://www.qt.io/download)
2. **Git** — скачать с [git-scm.com](https://git-scm.com/)
3. Компилятор C++ (идёт в комплекте с Qt Creator)

---

## 🏗 Архитектура проекта

Проект построен по принципу **MVC (Model-View-Controller)**:

```
┌─────────────────────────────────────────────────┐
│                    Qt UI (View)                 │
│  LoginWindow │ AdminPanel │ TeacherPanel │ ...  │
├─────────────────────────────────────────────────┤
│               Controllers (Логика)              │
│  AuthController │ CourseController │ ...        │
├─────────────────────────────────────────────────┤
│                Models (Данные)                  │
│  User │ Course │ Grade │ Enrollment │ ...       │
├─────────────────────────────────────────────────┤
│           DatabaseManager (Singleton)           │
│         Чтение/Запись JSON-файлов               │
└─────────────────────────────────────────────────┘
```

### Как это работает

1. **View (Представление)** — это Qt-окна (.ui файлы + классы окон). Они ТОЛЬКО отображают данные и принимают действия пользователя.
2. **Controller (Контроллер)** — обрабатывает логику. Например: проверка пароля, добавление курса, подсчёт оценок. Контроллер НЕ знает о Qt-виджетах.
3. **Model (Модель)** — описание данных. Класс `User` хранит имя, логин, роль. Класс `Course` хранит название, преподавателя, студентов.
4. **DatabaseManager** — единственный класс, который работает с файлами. Через него читаются и записываются ВСЕ JSON-файлы.

---

## 📁 Структура файлов и папок

```
OOP-project/
│
├── README.md                    ← Этот файл (документация)
├── StudyTable.pro               ← Файл проекта Qt (qmake)
├── main.cpp                     ← Точка входа в программу
│
├── models/                      ← Модели данных (классы-сущности)
│   ├── user.h / user.cpp        ← Класс User (пользователь)
│   ├── course.h / course.cpp    ← Класс Course (курс)
│   ├── grade.h / grade.cpp      ← Класс Grade (оценка)
│   └── enrollment.h / enrollment.cpp ← Класс Enrollment (запись на курс)
│
├── controllers/                 ← Контроллеры (бизнес-логика)
│   ├── authcontroller.h / .cpp  ← Логика авторизации
│   ├── coursecontroller.h / .cpp ← Логика управления курсами
│   ├── gradecontroller.h / .cpp ← Логика оценок
│   └── usercontroller.h / .cpp  ← Логика управления пользователями
│
├── views/                       ← Qt-окна (интерфейс)
│   ├── loginwindow.h / .cpp / .ui    ← Окно входа
│   ├── adminpanel.h / .cpp / .ui     ← Панель администратора
│   ├── teacherpanel.h / .cpp / .ui   ← Панель преподавателя
│   └── studentpanel.h / .cpp / .ui   ← Панель студента
│
├── database/                    ← Менеджер данных
│   └── databasemanager.h / .cpp ← Singleton для работы с JSON-файлами
│
├── resources/                   ← Ресурсы приложения
│   └── styles/
│       └── main.qss             ← Стили (как CSS, только для Qt)
│
└── data/                        ← JSON-файлы с данными
    ├── users.json               ← Все пользователи
    ├── courses.json             ← Все курсы
    ├── grades.json              ← Все оценки
    └── enrollments.json         ← Записи студентов на курсы
```

> ⚠️ **Важно:** Все участники ОБЯЗАНЫ придерживаться этой структуры. НЕ создавайте файлы в случайных местах.

---

## 🧱 Принципы ООП в проекте

Наш проект **обязан** демонстрировать все 4 принципа ООП. Вот как именно:

### 1. Инкапсуляция (Encapsulation)

Все поля классов — **private**. Доступ только через геттеры/сеттеры.

```cpp
class User {
private:
    QString m_name;
    QString m_login;
    QString m_password;
    QString m_role;    // "admin", "teacher", "student"

public:
    // Геттеры
    QString getName() const { return m_name; }
    QString getRole() const { return m_role; }

    // Сеттеры
    void setName(const QString& name) { m_name = name; }
};
```

### 2. Наследование (Inheritance)

Базовый класс `User` → дочерние классы `Admin`, `Teacher`, `Student`.

```cpp
class User {
public:
    virtual QString getDashboardTitle() const = 0; // чисто виртуальная
    virtual ~User() = default;
};

class Admin : public User {
public:
    QString getDashboardTitle() const override {
        return "Панель администратора";
    }
};

class Teacher : public User {
public:
    QString getDashboardTitle() const override {
        return "Панель преподавателя";
    }
};

class Student : public User {
public:
    QString getDashboardTitle() const override {
        return "Панель студента";
    }
};
```

### 3. Полиморфизм (Polymorphism)

Работаем через указатель на базовый класс — вызывается нужная версия метода.

```cpp
User* currentUser = authenticateUser(login, password);

// Полиморфизм — вызовется метод нужного дочернего класса
qDebug() << currentUser->getDashboardTitle();

// Открываем нужную панель в зависимости от роли
currentUser->openDashboard();
```

### 4. Абстракция (Abstraction)

Контроллеры и View работают с абстракциями — им не важно, КАК именно данные читаются/записываются.

```cpp
// Контроллер не знает, что данные лежат в JSON
// Он просто вызывает метод — и получает результат
QList<Course> courses = DatabaseManager::instance()->getAllCourses();
```

---

## 🎨 Паттерны проектирования

### Singleton — DatabaseManager

**Зачем?** Чтобы был ОДИН объект, который работает с файлами. Иначе два потока могут одновременно писать в файл → данные испортятся.

```cpp
class DatabaseManager {
private:
    static DatabaseManager* m_instance;
    DatabaseManager() {} // конструктор закрыт

public:
    static DatabaseManager* instance() {
        if (!m_instance) {
            m_instance = new DatabaseManager();
        }
        return m_instance;
    }

    // Методы для работы с данными
    QList<User> getAllUsers();
    void saveUser(const User& user);
    QList<Course> getAllCourses();
    void saveCourse(const Course& course);
    // ... и так далее
};
```

### MVC (Model-View-Controller)

| Компонент | Где находится | Что делает |
|-----------|---------------|------------|
| **Model** | `models/` | Описывает данные (User, Course, Grade) |
| **View** | `views/` | Qt-окна, кнопки, таблицы |
| **Controller** | `controllers/` | Логика: проверки, вычисления, маршрутизация |

**Правило:** View НИКОГДА напрямую не обращается к DatabaseManager. Всегда через Controller.

---

## 👥 Роли пользователей

В системе **3 роли** с разными правами:

### 🔴 Администратор (Admin)

| Действие | Описание |
|----------|----------|
| Управление пользователями | Создание, редактирование, удаление учётных записей |
| Управление курсами | Создание, редактирование, удаление курсов |
| Назначение преподавателей | Привязка преподавателя к курсу |
| Запись студентов | Запись/отчисление студентов на курсы |
| Просмотр статистики | Общая статистика: кол-во пользователей, курсов |

### 🟡 Преподаватель (Teacher)

| Действие | Описание |
|----------|----------|
| Просмотр своих курсов | Список курсов, где он преподаёт |
| Просмотр студентов | Список студентов на своих курсах |
| Выставление оценок | Добавление/редактирование оценок студентам |
| Статистика | Средний балл по своим курсам |

### 🟢 Студент (Student)

| Действие | Описание |
|----------|----------|
| Просмотр курсов | Список курсов, на которые записан |
| Просмотр оценок | Свои оценки по каждому курсу |
| Средний балл | Общий средний балл по всем курсам |

---

## 👨‍💻 Распределение работы по участникам

### Участник 1 — Модуль авторизации (Login)

**Что делает:** Окно входа + логика проверки пароля + маршрутизация по ролям.

**Файлы, за которые отвечает:**

- `views/loginwindow.h` / `loginwindow.cpp` / `loginwindow.ui`
- `controllers/authcontroller.h` / `authcontroller.cpp`
- `main.cpp` (точка входа, создание первого окна)

**Подробности:**

1. Создать UI окна входа — поля "Логин" и "Пароль", кнопка "Войти"
2. При нажатии "Войти" → `AuthController::authenticate(login, password)`
3. `AuthController` берёт список пользователей из `DatabaseManager`, ищет совпадение
4. Если найден → определяем роль → открываем нужную панель (Admin/Teacher/Student)
5. Если не найден → показываем ошибку "Неверный логин или пароль"
6. После успешного входа — Login-окно скрывается, открывается панель роли

**Логика маршрутизации (в AuthController или LoginWindow):**

```cpp
User* user = authController->authenticate(login, password);
if (!user) {
    showError("Неверный логин или пароль");
    return;
}

if (user->getRole() == "admin") {
    AdminPanel* panel = new AdminPanel(user);
    panel->show();
} else if (user->getRole() == "teacher") {
    TeacherPanel* panel = new TeacherPanel(user);
    panel->show();
} else if (user->getRole() == "student") {
    StudentPanel* panel = new StudentPanel(user);
    panel->show();
}
this->hide(); // скрываем окно входа
```

---

### Участник 2 — Модуль администратора (Admin Panel)

**Что делает:** Панель управления для администратора — CRUD пользователей и курсов.

**Файлы, за которые отвечает:**

- `views/adminpanel.h` / `adminpanel.cpp` / `adminpanel.ui`
- `controllers/usercontroller.h` / `usercontroller.cpp`
- `controllers/coursecontroller.h` / `coursecontroller.cpp`

**Подробности:**

1. **Главный экран** — Dashboard со статистикой:
   - Всего пользователей: X
   - Всего курсов: Y
   - Всего студентов: Z
   - Всего преподавателей: W

2. **Управление пользователями (вкладка/секция):**
   - Таблица со всеми пользователями (имя, логин, роль)
   - Кнопка "Добавить пользователя" → диалог с полями: имя, логин, пароль, роль
   - Кнопка "Редактировать" → редактирование выбранного пользователя
   - Кнопка "Удалить" → удаление с подтверждением

3. **Управление курсами (вкладка/секция):**
   - Таблица со всеми курсами (название, преподаватель, кол-во студентов)
   - Кнопка "Создать курс" → диалог: название курса, выбрать преподавателя из списка
   - Кнопка "Редактировать курс"
   - Кнопка "Удалить курс"
   - Кнопка "Записать студента на курс"

---

### Участник 3 — Модуль преподавателя (Teacher Panel)

**Что делает:** Панель преподавателя — просмотр своих курсов и выставление оценок.

**Файлы, за которые отвечает:**

- `views/teacherpanel.h` / `teacherpanel.cpp` / `teacherpanel.ui`
- `controllers/gradecontroller.h` / `gradecontroller.cpp`

**Подробности:**

1. **Dashboard** — приветствие + статистика:
   - "Добро пожаловать, [Имя]!"
   - Ваших курсов: X
   - Общее кол-во студентов: Y
   - Средний балл по вашим курсам: Z

2. **Мои курсы (вкладка):**
   - Таблица курсов, где текущий преподаватель ведёт
   - При клике на курс → показать список студентов этого курса

3. **Оценки (вкладка):**
   - Выбрать курс → показать таблицу: Студент | Оценка
   - Возможность добавить/изменить оценку
   - `GradeController::setGrade(studentId, courseId, grade)`
   - Оценка сохраняется через `DatabaseManager`

---

### Участник 4 — Модуль студента (Student Panel)

**Что делает:** Панель студента — просмотр курсов и оценок.

**Файлы, за которые отвечает:**

- `views/studentpanel.h` / `studentpanel.cpp` / `studentpanel.ui`
- Может использовать `GradeController` (от Участника 3) для чтения оценок

**Подробности:**

1. **Dashboard** — приветствие + статистика:
   - "Добро пожаловать, [Имя]!"
   - Записан на курсов: X
   - Средний балл: Y

2. **Мои курсы (вкладка):**
   - Таблица: Название курса | Преподаватель | Оценка
   - Данные берутся из `enrollments.json` + `courses.json` + `grades.json`

3. **Оценки (вкладка):**
   - Детальная таблица: Курс | Оценка | Дата
   - Показать средний балл внизу таблицы

---

### Участник 5 — Файловый ввод/вывод и интеграция (Database & Core)

**Что делает:** Ядро проекта — `DatabaseManager` (Singleton), все модели данных, связка окон.

**Файлы, за которые отвечает:**

- `database/databasemanager.h` / `databasemanager.cpp`
- `models/user.h` / `user.cpp`
- `models/course.h` / `course.cpp`
- `models/grade.h` / `grade.cpp`
- `models/enrollment.h` / `enrollment.cpp`
- `data/users.json`, `courses.json`, `grades.json`, `enrollments.json`
- `resources/styles/main.qss`
- `StudyTable.pro` (файл проекта)

**Подробности:**

1. **DatabaseManager (Singleton):**

   ```cpp
   // Основные методы, которые нужно реализовать:

   // Пользователи
   QList<User> getAllUsers();
   User getUserById(int id);
   User getUserByLogin(const QString& login);
   void addUser(const User& user);
   void updateUser(const User& user);
   void deleteUser(int id);

   // Курсы
   QList<Course> getAllCourses();
   QList<Course> getCoursesByTeacherId(int teacherId);
   QList<Course> getCoursesByStudentId(int studentId);
   void addCourse(const Course& course);
   void updateCourse(const Course& course);
   void deleteCourse(int id);

   // Оценки
   QList<Grade> getGradesByStudentId(int studentId);
   QList<Grade> getGradesByCourseId(int courseId);
   void addGrade(const Grade& grade);
   void updateGrade(const Grade& grade);

   // Записи на курсы
   QList<Enrollment> getEnrollmentsByStudentId(int studentId);
   QList<Enrollment> getEnrollmentsByCourseId(int courseId);
   void addEnrollment(const Enrollment& enrollment);
   void deleteEnrollment(int id);
   ```

2. **Модели данных:**
   Каждый модельный класс должен уметь:
   - Создаваться из `QJsonObject` (метод `fromJson`)
   - Конвертироваться в `QJsonObject` (метод `toJson`)

   ```cpp
   class User {
   public:
       static User fromJson(const QJsonObject& json);
       QJsonObject toJson() const;
   };
   ```

3. **Тестовые данные** — создать начальные JSON-файлы (см. секцию "Формат данных").

4. **Стили (main.qss)** — единый файл стилей для тёмной темы.

5. **Файл проекта (StudyTable.pro)** — подключение всех файлов, модулей Qt.

---

## 📦 Формат данных (JSON)

### users.json

```json
[
  {
    "id": 1,
    "name": "Абдуллох Неъматуллоев",
    "login": "admin",
    "password": "admin123",
    "role": "admin"
  },
  {
    "id": 2,
    "name": "Иванов Алексей",
    "login": "teacher1",
    "password": "teach123",
    "role": "teacher"
  },
  {
    "id": 3,
    "name": "Петрова Мария",
    "login": "student1",
    "password": "stud123",
    "role": "student"
  }
]
```

### courses.json

```json
[
  {
    "id": 1,
    "name": "Математика",
    "description": "Высшая математика, 1 семестр",
    "teacherId": 2
  },
  {
    "id": 2,
    "name": "Программирование C++",
    "description": "Основы ООП на C++",
    "teacherId": 2
  }
]
```

### grades.json

```json
[
  {
    "id": 1,
    "studentId": 3,
    "courseId": 1,
    "value": 85,
    "date": "2026-02-28"
  }
]
```

### enrollments.json

```json
[
  {
    "id": 1,
    "studentId": 3,
    "courseId": 1,
    "enrolledDate": "2026-02-01"
  },
  {
    "id": 2,
    "studentId": 3,
    "courseId": 2,
    "enrolledDate": "2026-02-01"
  }
]
```

---

## 🚀 Как собрать и запустить проект

### Способ 1: Через Qt Creator (рекомендуется)

```
1. Открыть Qt Creator
2. File → Open File or Project → выбрать StudyTable.pro
3. Выбрать комплект (Desktop Qt 6.x.x)
4. Нажать зелёный треугольник ▶ (Run)
```

### Способ 2: Через терминал

```bash
# Перейти в папку проекта
cd /path/to/OOP-project

# Сгенерировать Makefile
qmake StudyTable.pro

# Собрать проект
make

# Запустить
./StudyTable        # Linux
open StudyTable.app # macOS
StudyTable.exe      # Windows
```

### Тестовые аккаунты

| Роль | Логин | Пароль |
|------|-------|--------|
| Администратор | `admin` | `admin123` |
| Преподаватель | `teacher1` | `teach123` |
| Студент | `student1` | `stud123` |

---

## 🌿 Git-воркфлоу команды

### Ветвление

Каждый участник работает **в своей ветке**, НЕ в `main`.

```bash
# Создать свою ветку от main
git checkout main
git pull origin main
git checkout -b feature/login        # Участник 1
git checkout -b feature/admin-panel  # Участник 2
git checkout -b feature/teacher-panel # Участник 3
git checkout -b feature/student-panel # Участник 4
git checkout -b feature/database     # Участник 5
```

### Ежедневная работа

```bash
# 1. Убедитесь, что вы в своей ветке
git branch   # текущая ветка помечена *

# 2. Напишите код

# 3. Сохраните изменения
git add .
git commit -m "feat: добавил окно входа"

# 4. Отправьте на GitHub
git push origin feature/login
```

### Слияние в main

```bash
# Когда ваш модуль готов:
# 1. Сначала обновите свою ветку
git checkout main
git pull origin main
git checkout feature/login
git merge main              # вливаем main в свою ветку

# 2. Решите конфликты если есть

# 3. Создайте Pull Request на GitHub
# или слейте через терминал:
git checkout main
git merge feature/login
git push origin main
```

### Правила коммитов

Используйте понятные префиксы:

```
feat: добавил окно входа
fix: исправил проверку пароля
style: обновил стили панели
refactor: переписал DatabaseManager
docs: обновил README
```

---

## 🧪 Аккаунты для тестирования

При первом запуске данные загружаются из папки `data/`.  
Участник 5 создаёт начальные JSON-файлы с тестовыми данными:

| # | Имя | Логин | Пароль | Роль |
|---|-----|-------|--------|------|
| 1 | Админ | admin | admin123 | Администратор |
| 2 | Иванов А. | teacher1 | teach123 | Преподаватель |
| 3 | Сидоров Б. | teacher2 | teach123 | Преподаватель |
| 4 | Петрова М. | student1 | stud123 | Студент |
| 5 | Козлов Д. | student2 | stud123 | Студент |
| 6 | Смирнова А. | student3 | stud123 | Студент |

---

## 📐 Правила и договорённости

### Стиль кода

- Имена классов: `PascalCase` → `LoginWindow`, `DatabaseManager`
- Имена методов: `camelCase` → `getAllUsers()`, `setGrade()`
- Приватные поля: с префиксом `m_` → `m_name`, `m_login`
- Файлы: `lowercase` → `loginwindow.h`, `databasemanager.cpp`
- Отступы: **4 пробела** (не табы)

### Кто от кого зависит

```
Участник 5 (Database + Models) ← делает ПЕРВЫМ
    ↓
Участник 1 (Login) ← нужны User и DatabaseManager
    ↓
Участники 2, 3, 4 (Панели) ← нужны Login, Models, Database
```

> ⚠️ **Участник 5 начинает первым!** Остальные могут начинать UI-часть, но для логики им нужны модели и DatabaseManager.

### Порядок работы

1. **Неделя 1:** Участник 5 создаёт модели + DatabaseManager + тестовые JSON → пушит в `main`
2. **Неделя 1:** Участник 1 параллельно делает UI окна входа (заглушки для логики)
3. **Неделя 2:** Участник 1 подключает реальную логику входа. Участники 2, 3, 4 начинают свои панели
4. **Неделя 3:** Все доделывают → тестирование → слияние → финальная проверка

### Общение

- Если что-то не понятно — **спрашивайте в чате команды**
- Если нужен метод от другого участника — **создайте issue на GitHub** или напишите ему
- Перед слиянием — **проверьте, что проект компилируется** и работает

---

## 📊 Диаграмма классов (упрощённая)

```
                    ┌──────────┐
                    │   User   │ (abstract)
                    ├──────────┤
                    │ -m_id    │
                    │ -m_name  │
                    │ -m_login │
                    │ -m_pass  │
                    │ -m_role  │
                    ├──────────┤
                    │ +fromJson│
                    │ +toJson  │
                    │ +getRole │
                    └────┬─────┘
                         │ наследование
            ┌────────────┼────────────┐
            ▼            ▼            ▼
       ┌─────────┐ ┌──────────┐ ┌──────────┐
       │  Admin  │ │ Teacher  │ │ Student  │
       └─────────┘ └──────────┘ └──────────┘

  ┌──────────┐     ┌──────────┐     ┌─────────────┐
  │  Course  │     │  Grade   │     │ Enrollment  │
  ├──────────┤     ├──────────┤     ├─────────────┤
  │ -m_id    │     │ -m_id    │     │ -m_id       │
  │ -m_name  │     │ -studentId│    │ -studentId  │
  │ -m_desc  │     │ -courseId │     │ -courseId   │
  │-teacherId│     │ -value   │     │ -date       │
  └──────────┘     │ -date    │     └─────────────┘
                   └──────────┘

  ┌─────────────────────────────┐
  │     DatabaseManager         │
  │      (SINGLETON)            │
  ├─────────────────────────────┤
  │ -static m_instance          │
  │ -DatabaseManager() private  │
  ├─────────────────────────────┤
  │ +static instance()          │
  │ +getAllUsers()               │
  │ +getAllCourses()             │
  │ +getGradesByStudentId()     │
  │ +saveCourse()               │
  │ +addUser()                  │
  │ ... и др.                   │
  └─────────────────────────────┘
```

---

> 💡 **Если ты прочитал это до конца — ты уже понимаешь, что делать. Начинай с создания своих файлов в своей ветке!**
