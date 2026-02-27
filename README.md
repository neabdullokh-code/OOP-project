# 📚 Study.Table(); — CRM-система для учебных центров

> **Предмет:** Объектно-ориентированное программирование (ООП)  
> **Технологии:** C++ / Qt Framework  
> **Команда:** 5 участников  
> **Архитектура:** Vertical Slice Architecture

---

## 📋 Оглавление

1. [Описание проекта](#-описание-проекта)
2. [Архитектура и принципы ООП](#-архитектура-и-принципы-ооп)
3. [Структура проекта (папки и файлы)](#-структура-проекта)
4. [Модули и распределение задач](#-модули-и-распределение-задач)
5. [Паттерны проектирования](#-паттерны-проектирования)
6. [Классы и сущности](#-классы-и-сущности)
7. [Хранение данных](#-хранение-данных)
8. [Рабочий процесс (Git Workflow)](#-рабочий-процесс-git-workflow)
9. [Как запустить проект](#-как-запустить-проект)
10. [Полезные ссылки](#-полезные-ссылки)

---

## 🎯 Описание проекта

**Study.Table();** — это полноценная CRM-система с графическим интерфейсом (GUI) для автоматизации работы учебных центров. Система управляет пользователями, курсами, расписанием, оценками, посещаемостью и аналитикой.

### Что конкретно делает программа:
- 🔐 **Авторизация** — вход по логину/паролю с разными ролями (Админ, Преподаватель, Студент)
- 👤 **Управление пользователями** — админ может создавать/банить/замораживать аккаунты
- 🎓 **Управление курсами** — создание курсов, назначение преподавателей, прикрепление студентов
- 📝 **Задания и оценки** — выдача заданий, приём работ, выставление оценок с разными алгоритмами
- 📅 **Расписание и посещаемость** — составление расписания, отметка посещаемости
- 📊 **Аналитика и экспорт** — статистика, отчёты в PDF/CSV, журнал действий (Audit Log)

---

## 🏗 Архитектура и принципы ООП

Проект **строго** следует четырём столпам ООП и принципам SOLID.

### 4 столпа ООП в нашем проекте:

| Принцип | Как используется | Пример в коде |
|---|---|---|
| **Абстракция** | Все компоненты взаимодействуют через абстрактные классы и интерфейсы | `IUser`, `IExportable`, `IGradingStrategy` |
| **Инкапсуляция** | Приватные данные, доступ только через геттеры/сеттеры и `signals/slots` | Пароли, оценки, конфигурации — всё `private` |
| **Наследование** | Иерархия классов: общие свойства вынесены в базовые классы | `SystemEntity` → `Course`, `Assignment` и т.д. |
| **Полиморфизм** | Виртуальные функции для рендера разных дашбордов в зависимости от роли | `virtual void setupDashboard() = 0;` |

### SOLID принципы:

- **S** (Single Responsibility) — каждый класс отвечает за одну задачу
- **O** (Open/Closed) — классы открыты для расширения, закрыты для модификации
- **L** (Liskov Substitution) — дочерние классы полностью заменяют родительские
- **I** (Interface Segregation) — мелкие интерфейсы вместо одного огромного
- **D** (Dependency Inversion) — зависимость от абстракций, а не от конкретных классов

---

## 📁 Структура проекта

```
OOP-project/
├── README.md                     # Этот файл
├── StudyTable.pro                # Qt проект файл
│
├── src/                          # Весь исходный код
│   ├── main.cpp                  # Точка входа
│   │
│   ├── core/                     # Ядро системы (общие базовые классы)
│   │   ├── SystemEntity.h/cpp    # Базовый класс для всех сущностей (id, timestamps)
│   │   ├── interfaces/           # Абстрактные интерфейсы
│   │   │   ├── IUser.h           # Интерфейс пользователя
│   │   │   ├── IExportable.h     # Интерфейс для экспорта данных
│   │   │   └── ISerializable.h   # Интерфейс для сериализации в JSON
│   │   └── DatabaseManager.h/cpp # Singleton — менеджер файлов/данных
│   │
│   ├── auth/                     # Модуль 1: Авторизация и RBAC
│   │   ├── models/
│   │   │   ├── User.h/cpp        # Класс пользователя
│   │   │   ├── Role.h/cpp        # Класс роли
│   │   │   ├── Permission.h/cpp  # Класс разрешения
│   │   │   └── Session.h/cpp     # Класс сессии
│   │   ├── services/
│   │   │   ├── AuthService.h/cpp # Логика авторизации
│   │   │   └── SessionManager.h/cpp # Singleton — менеджер сессий
│   │   ├── factories/
│   │   │   ├── UserFactory.h/cpp # Factory Method — создание пользователей
│   │   │   └── PanelFactory.h/cpp# Factory Method — создание UI панелей
│   │   └── ui/
│   │       ├── LoginWindow.h/cpp # Окно входа
│   │       ├── AdminPanel.h/cpp  # Панель администратора
│   │       └── RoleEditor.h/cpp  # Редактор ролей
│   │
│   ├── courses/                  # Модуль 2: Управление курсами
│   │   ├── models/
│   │   │   ├── Course.h/cpp      # Класс курса
│   │   │   ├── Subject.h/cpp     # Класс предмета
│   │   │   └── Classroom.h/cpp   # Класс аудитории
│   │   ├── services/
│   │   │   └── CourseService.h/cpp # Бизнес-логика курсов
│   │   └── ui/
│   │       ├── CourseListView.h/cpp    # Список курсов
│   │       ├── CourseDetailView.h/cpp  # Детали курса
│   │       └── CourseFormDialog.h/cpp  # Форма создания/редактирования
│   │
│   ├── performance/              # Модуль 3: Задания и оценки
│   │   ├── models/
│   │   │   ├── Assignment.h/cpp  # Класс задания
│   │   │   ├── Submission.h/cpp  # Класс отправки работы
│   │   │   └── Grade.h/cpp       # Класс оценки
│   │   ├── strategies/
│   │   │   ├── IGradingStrategy.h        # Интерфейс стратегии оценивания
│   │   │   ├── StandardGrading.h/cpp     # Стандартный процентный расчёт
│   │   │   └── CurveGrading.h/cpp        # Оценивание по кривой
│   │   ├── services/
│   │   │   └── GradingService.h/cpp      # Сервис оценивания
│   │   └── ui/
│   │       ├── AssignmentView.h/cpp      # Просмотр заданий
│   │       ├── SubmissionDialog.h/cpp    # Диалог отправки работы
│   │       └── GradeBookView.h/cpp       # Журнал оценок
│   │
│   ├── attendance/               # Модуль 4: Расписание и посещаемость
│   │   ├── models/
│   │   │   ├── Schedule.h/cpp          # Класс расписания
│   │   │   └── AttendanceRecord.h/cpp  # Класс записи посещаемости
│   │   ├── services/
│   │   │   ├── ScheduleService.h/cpp   # Сервис расписания
│   │   │   └── AttendanceService.h/cpp # Сервис посещаемости
│   │   └── ui/
│   │       ├── TimetableView.h/cpp     # Вид расписания
│   │       └── AttendanceView.h/cpp    # Вид посещаемости
│   │
│   └── analytics/                # Модуль 5: Аналитика и экспорт
│       ├── models/
│       │   └── AuditLog.h/cpp          # Класс журнала действий
│       ├── strategies/
│       │   ├── IExportStrategy.h       # Интерфейс стратегии экспорта
│       │   ├── PdfExportStrategy.h/cpp # Экспорт в PDF
│       │   └── CsvExportStrategy.h/cpp # Экспорт в CSV
│       ├── services/
│       │   ├── AnalyticsService.h/cpp  # Сервис аналитики
│       │   └── ExportService.h/cpp     # Сервис экспорта
│       └── ui/
│           ├── DashboardView.h/cpp     # Панель аналитики
│           └── ReportDialog.h/cpp      # Диалог генерации отчётов
│
├── data/                         # Данные (JSON файлы)
│   ├── users.json
│   ├── roles.json
│   ├── courses.json
│   ├── assignments.json
│   ├── grades.json
│   ├── schedules.json
│   ├── attendance.json
│   └── audit_log.json
│
├── resources/                    # Ресурсы Qt (иконки, стили)
│   ├── icons/
│   └── styles/
│       └── main.qss              # Qt StyleSheet (тема оформления)
│
└── docs/                         # Документация
    ├── class_diagram.png         # UML диаграмма классов
    └── architecture.md           # Описание архитектуры
```

---

## 👥 Модули и распределение задач

> ⚠️ **Важно:** Мы используем **Vertical Slice Architecture**. Это значит, что каждый участник делает свой модуль **полностью** — от хранения данных (JSON) до интерфейса (Qt UI). Так каждый из нас понимает все слои системы.

---

### 🔐 Модуль 1: Авторизация и RBAC (Auth & RBAC)
**Участник 1**

**Что делаешь:**
Создаёшь всю систему входа и управления ролями. Это фундамент всего проекта — остальные модули зависят от тебя.

**Конкретные задачи:**

| # | Задача | Подробнее |
|---|--------|-----------|
| 1 | Класс `User` | Поля: `id`, `username`, `passwordHash`, `fullName`, `email`, `roleId`, `status` (Active/Frozen/Banned), `createdAt`. Наследуется от `SystemEntity`. Реализует `IUser` и `ISerializable`. |
| 2 | Класс `Role` | Поля: `id`, `name`, `permissions` (QList<Permission>). Методы: `hasPermission()`, `addPermission()`, `removePermission()`. |
| 3 | Класс `Permission` | Enum-подобный класс. Примеры: `CAN_CREATE_COURSE`, `CAN_EDIT_GRADES`, `CAN_VIEW_ANALYTICS`, `CAN_MANAGE_USERS` и т.д. |
| 4 | Класс `Session` | Хранит текущего залогиненного пользователя, время входа, статус сессии. |
| 5 | `AuthService` | Логика: проверка логина/пароля, хэширование паролей, создание сессии. |
| 6 | `SessionManager` | **Singleton!** Один экземпляр на всё приложение. Хранит текущую сессию, проверяет права доступа. |
| 7 | `UserFactory` | **Factory Method!** На вход — данные пользователя, на выход — готовый объект нужного типа (`Admin`, `Student`, `Professor`). |
| 8 | `PanelFactory` | **Factory Method!** По ролям и разрешениям создаёт нужные Qt-виджеты для каждой роли. |
| 9 | `LoginWindow` (UI) | Окно входа: логин, пароль, кнопка "Войти". Валидация полей. |
| 10 | `AdminPanel` (UI) | Панель админа: список пользователей, кнопки бан/разбан/заморозка, создание новых пользователей. |
| 11 | `RoleEditor` (UI) | Интерфейс для создания/редактирования ролей: чекбоксы с разрешениями. |
| 12 | Сериализация | Чтение/запись `users.json` и `roles.json`. |

**Что ты используешь из паттернов:**
- ✅ **Singleton** — `SessionManager`
- ✅ **Factory Method** — `UserFactory`, `PanelFactory`

**Зависимости:** Модуль `core/` (базовые классы). Все остальные модули зависят от твоего модуля.

---

### 📘 Модуль 2: Управление курсами (Course Management)
**Участник 2**

**Что делаешь:**
Создаёшь всё, что связано с курсами, предметами и аудиториями. Студенты записываются на курсы, преподаватели назначаются к ним.

**Конкретные задачи:**

| # | Задача | Подробнее |
|---|--------|-----------|
| 1 | Класс `Course` | Поля: `id`, `title`, `description`, `subjectId`, `professorId`, `studentIds` (QList), `startDate`, `endDate`, `status`. Наследуется от `SystemEntity`. |
| 2 | Класс `Subject` | Поля: `id`, `name`, `code` (например "MATH101"), `description`. |
| 3 | Класс `Classroom` | Поля: `id`, `roomNumber`, `capacity`, `equipment` (QStringList — проектор, доска и т.д.). |
| 4 | `CourseService` | Бизнес-логика: создание курсов, назначение преподавателя, запись/удаление студентов, проверка конфликтов (один преподаватель — две пары одновременно). |
| 5 | `CourseListView` (UI) | Таблица/список всех курсов с фильтрами (по предмету, преподавателю, статусу). |
| 6 | `CourseDetailView` (UI) | Подробная страница курса: инфо, список студентов, расписание, задания. |
| 7 | `CourseFormDialog` (UI) | Диалоговое окно для создания/редактирования курса. Выбор предмета, преподавателя из выпадающего списка. |
| 8 | Сериализация | Чтение/запись `courses.json`. |

**Зависимости:** 
- Модуль `auth/` — для получения списка преподавателей и студентов (по ролям)
- Модуль `core/` — базовые классы

---

### 📝 Модуль 3: Задания и оценки (Performance)
**Участник 3**

**Что делаешь:**
Создаёшь систему домашних заданий, сдачи работ и оценивания. Здесь ключевой паттерн — **Strategy** для разных алгоритмов оценивания.

**Конкретные задачи:**

| # | Задача | Подробнее |
|---|--------|-----------|
| 1 | Класс `Assignment` | Поля: `id`, `courseId`, `title`, `description`, `dueDate`, `maxScore`, `createdBy`. |
| 2 | Класс `Submission` | Поля: `id`, `assignmentId`, `studentId`, `content` (текст или путь к файлу), `submittedAt`, `status` (Pending/Graded). |
| 3 | Класс `Grade` | Поля: `id`, `submissionId`, `studentId`, `courseId`, `score`, `feedback`, `gradedBy`, `gradedAt`. |
| 4 | `IGradingStrategy` | **Абстрактный интерфейс!** Метод: `virtual double calculateGrade(double rawScore, double maxScore, ...) = 0;` |
| 5 | `StandardGrading` | Реализация стратегии: обычный процентный расчёт `(score / maxScore) * 100`. |
| 6 | `CurveGrading` | Реализация стратегии: оценка по кривой (учитывает средний балл группы, стандартное отклонение). |
| 7 | `GradingService` | Сервис, который принимает стратегию и считает оценки. Можно переключать стратегию **динамически**. |
| 8 | `AssignmentView` (UI) | Список заданий курса. Преподаватель видит все, студент — только свои. |
| 9 | `SubmissionDialog` (UI) | Диалог отправки работы: текстовое поле или загрузка файла. |
| 10 | `GradeBookView` (UI) | Журнал оценок: таблица с оценками по студентам и заданиям. |
| 11 | Сериализация | Чтение/запись `assignments.json`, `grades.json`. |

**Что ты используешь из паттернов:**
- ✅ **Strategy** — `IGradingStrategy`, `StandardGrading`, `CurveGrading`
- ✅ **Полиморфизм** — стратегия переключается на лету

**Зависимости:**
- Модуль `auth/` — для определения роли (преподаватель/студент)
- Модуль `courses/` — задания привязаны к курсам

---

### 📅 Модуль 4: Расписание и посещаемость (Attendance & Scheduling)
**Участник 4**

**Что делаешь:**
Создаёшь систему расписания занятий и учёта посещаемости. Преподаватели отмечают, студенты смотрят своё расписание.

**Конкретные задачи:**

| # | Задача | Подробнее |
|---|--------|-----------|
| 1 | Класс `Schedule` | Поля: `id`, `courseId`, `classroomId`, `dayOfWeek`, `startTime`, `endTime`, `recurring` (bool). |
| 2 | Класс `AttendanceRecord` | Поля: `id`, `scheduleId`, `studentId`, `date`, `status` (Present/Absent/Late/Excused), `markedBy`. |
| 3 | `ScheduleService` | Бизнес-логика: создание занятий, проверка конфликтов аудиторий и преподавателей, фильтрация по дню/курсу. |
| 4 | `AttendanceService` | Бизнес-логика: отметка посещаемости, подсчёт статистики (% посещаемости студента). |
| 5 | `TimetableView` (UI) | Таблица расписания на неделю. Ячейки окрашены по предметам. Можно фильтровать по группе/преподавателю. |
| 6 | `AttendanceView` (UI) | Список студентов с чекбоксами для отметки (Present, Absent, Late). Сводная статистика. |
| 7 | Сериализация | Чтение/запись `schedules.json`, `attendance.json`. |

**Зависимости:**
- Модуль `auth/` — роль определяет, кто может отмечать посещаемость
- Модуль `courses/` — расписание привязано к курсам и аудиториям

---

### 📊 Модуль 5: Аналитика и экспорт (Analytics & Export)
**Участник 5**

**Что делаешь:**
Создаёшь систему аналитики, отчётов и журнала действий. Здесь паттерн **Strategy** используется для разных форматов экспорта (PDF/CSV).

**Конкретные задачи:**

| # | Задача | Подробнее |
|---|--------|-----------|
| 1 | Класс `AuditLog` | Поля: `id`, `userId`, `action` (строка, напр. "CREATED_COURSE"), `targetEntity`, `targetId`, `timestamp`, `details`. |
| 2 | `IExportStrategy` | **Абстрактный интерфейс!** Метод: `virtual void exportData(const QJsonArray& data, const QString& filePath) = 0;` |
| 3 | `PdfExportStrategy` | Реализация экспорта в PDF (через QPdfWriter или QPrinter). |
| 4 | `CsvExportStrategy` | Реализация экспорта в CSV (простая запись через QTextStream). |
| 5 | `AnalyticsService` | Подсчёт статистики: средний балл по курсу, рейтинг студентов, % посещаемости, топ курсов и т.д. |
| 6 | `ExportService` | Сервис экспорта: принимает стратегию и данные, генерирует файл. |
| 7 | `DashboardView` (UI) | Панель аналитики: графики, диаграммы (можно использовать `QChart`), сводная информация. |
| 8 | `ReportDialog` (UI) | Диалог генерации отчёта: выбор типа данных, периода, формата (PDF/CSV). |
| 9 | Сериализация | Чтение/запись `audit_log.json`. Также чтение данных из других JSON-файлов для построения аналитики. |

**Что ты используешь из паттернов:**
- ✅ **Strategy** — `IExportStrategy`, `PdfExportStrategy`, `CsvExportStrategy`

**Зависимости:**
- Все остальные модули — аналитика читает данные из всех JSON-файлов

---

## 🧩 Паттерны проектирования (Design Patterns)

### 1. Singleton (Одиночка)

**Зачем:** Гарантирует, что существует только **один** экземпляр класса.

**Где используется:**
- `DatabaseManager` — один менеджер файлов на всё приложение
- `SessionManager` — одна сессия пользователя

**Как реализовать:**
```cpp
class SessionManager {
public:
    static SessionManager& instance() {
        static SessionManager inst;
        return inst;
    }
    
    // Запрещаем копирование
    SessionManager(const SessionManager&) = delete;
    SessionManager& operator=(const SessionManager&) = delete;

    // Методы
    void login(const User& user);
    void logout();
    User currentUser() const;
    bool hasPermission(Permission perm) const;

private:
    SessionManager() = default; // Приватный конструктор!
    Session m_currentSession;
};
```

---

### 2. Factory Method (Фабричный метод)

**Зачем:** Создаёт объекты нужного типа, не привязываясь к конкретному классу.

**Где используется:**
- `UserFactory` — создаёт `Admin`, `Student`, `Professor` по данным из JSON
- `PanelFactory` — создаёт нужные Qt-виджеты по роли пользователя

**Как реализовать:**
```cpp
class UserFactory {
public:
    static User* createUser(const QJsonObject& data) {
        QString role = data["role"].toString();
        
        if (role == "admin")
            return new Admin(data);
        else if (role == "professor")
            return new Professor(data);
        else if (role == "student")
            return new Student(data);
        
        return nullptr;
    }
};
```

---

### 3. Strategy (Стратегия)

**Зачем:** Позволяет менять алгоритм **на лету**, не меняя код класса, который его использует.

**Где используется:**
- **Оценивание:** `StandardGrading` vs `CurveGrading`
- **Экспорт:** `PdfExportStrategy` vs `CsvExportStrategy`

**Как реализовать:**
```cpp
// Интерфейс стратегии
class IGradingStrategy {
public:
    virtual ~IGradingStrategy() = default;
    virtual double calculate(double rawScore, double maxScore) = 0;
};

// Конкретная стратегия
class StandardGrading : public IGradingStrategy {
public:
    double calculate(double rawScore, double maxScore) override {
        return (rawScore / maxScore) * 100.0;
    }
};

// Использование
class GradingService {
    IGradingStrategy* m_strategy;
public:
    void setStrategy(IGradingStrategy* strategy) {
        m_strategy = strategy;
    }
    double grade(double raw, double max) {
        return m_strategy->calculate(raw, max);
    }
};
```

---

## 📦 Классы и сущности

### Диаграмма зависимостей модулей:

```
┌──────────────────────────────────────────────────────┐
│                    core/                              │
│  SystemEntity, IUser, IExportable, ISerializable      │
│  DatabaseManager (Singleton)                          │
└───────┬──────────────────────────────────┬────────────┘
        │                                  │
        ▼                                  ▼
┌───────────────┐    ┌──────────────┐  ┌──────────────┐
│  auth/        │    │  courses/    │  │ attendance/  │
│  User, Role   │◄───│  Course      │  │ Schedule     │
│  Permission   │    │  Subject     │  │ Attendance   │
│  Session      │    │  Classroom   │  │ Record       │
│  AuthService  │    │  CourseServ  │  │              │
│  SessionMgr   │    └──────┬───────┘  └──────┬───────┘
│  Factories    │           │                 │
└───────┬───────┘           │                 │
        │                   ▼                 ▼
        │           ┌──────────────┐  ┌──────────────┐
        └──────────►│ performance/ │  │  analytics/  │
                    │ Assignment   │  │  AuditLog    │
                    │ Submission   │  │  Export      │
                    │ Grade        │  │  Analytics   │
                    │ Strategies   │  │  Strategies  │
                    └──────────────┘  └──────────────┘
```

### Базовый класс `SystemEntity`:

Все сущности наследуются от него — это обеспечивает единообразие:

```cpp
class SystemEntity {
protected:
    QString m_id;          // Уникальный ID (UUID)
    QDateTime m_createdAt; // Время создания
    QDateTime m_updatedAt; // Время обновления

public:
    SystemEntity();
    virtual ~SystemEntity() = default;
    
    QString id() const;
    QDateTime createdAt() const;
    QDateTime updatedAt() const;
    
    // Сериализация
    virtual QJsonObject toJson() const = 0;
    virtual void fromJson(const QJsonObject& json) = 0;
};
```

---

## 💾 Хранение данных

Все данные хранятся в **JSON-файлах** в папке `data/`.

### Пример `users.json`:
```json
[
  {
    "id": "usr-001",
    "username": "admin",
    "passwordHash": "a1b2c3d4e5...",
    "fullName": "Иванов Иван",
    "email": "admin@study.table",
    "roleId": "role-admin",
    "status": "Active",
    "createdAt": "2026-01-15T10:00:00"
  }
]
```

### Пример `roles.json`:
```json
[
  {
    "id": "role-admin",
    "name": "Super Administrator",
    "permissions": [
      "CAN_MANAGE_USERS",
      "CAN_CREATE_COURSE",
      "CAN_EDIT_GRADES",
      "CAN_VIEW_ANALYTICS",
      "CAN_EXPORT_DATA",
      "CAN_MANAGE_ROLES"
    ]
  },
  {
    "id": "role-professor",
    "name": "Professor",
    "permissions": [
      "CAN_CREATE_COURSE",
      "CAN_EDIT_GRADES",
      "CAN_MARK_ATTENDANCE"
    ]
  }
]
```

### `DatabaseManager` (Singleton):

```cpp
class DatabaseManager {
public:
    static DatabaseManager& instance();
    
    QJsonArray loadCollection(const QString& filename);  // Загрузить JSON
    void saveCollection(const QString& filename, const QJsonArray& data); // Сохранить JSON
    
private:
    DatabaseManager();
    QString m_dataPath; // Путь к папке data/
};
```

---

## 🔀 Рабочий процесс (Git Workflow)

### Ветки:

| Ветка | Назначение |
|-------|-----------|
| `main` | Стабильная версия (сюда пушим только проверенный код) |
| `develop` | Общая ветка разработки |
| `feature/auth` | Модуль авторизации |
| `feature/courses` | Модуль курсов |
| `feature/performance` | Модуль заданий и оценок |
| `feature/attendance` | Модуль расписания |
| `feature/analytics` | Модуль аналитики |

### Порядок работы:

1. **Перед началом работы** — `git pull origin develop`
2. **Создай свою ветку** — `git checkout -b feature/имя-модуля`
3. **Работай в своей ветке** — коммить часто, с понятными сообщениями
4. **Когда готово** — создай Pull Request (PR) в `develop`
5. **Код-ревью** — хотя бы один другой участник должен проверить PR
6. **Мержим** — после одобрения мержим в `develop`

### Правила коммитов:

```
feat: добавил LoginWindow с валидацией полей
fix: исправил баг с сохранением ролей в JSON
refactor: вынес UserFactory в отдельный файл
docs: обновил README.md
style: отформатировал код CourseService
```

---

## 🚀 Как запустить проект

### Требования:
- **Qt 6.x** (скачать: [qt.io](https://www.qt.io/download))
- **C++ 17** (или выше)
- **Qt Creator** (IDE, идёт вместе с Qt)
- **Git**

### Шаги:

```bash
# 1. Клонируем репозиторий
git clone <URL_РЕПОЗИТОРИЯ>
cd OOP-project

# 2. Переключаемся на ветку разработки
git checkout develop

# 3. Открываем проект в Qt Creator
# Файл → Открыть файл или проект → выбираем StudyTable.pro

# 4. Собираем и запускаем
# Нажимаем зелёный треугольник ▶ (Run) в Qt Creator
```

---

## 📅 План-график работы

| Неделя | Задачи | Ответственные |
|--------|--------|---------------|
| **1** | Настройка проекта, `core/`, базовые классы, `DatabaseManager` | Все вместе |
| **2** | Модуль авторизации (login, RBAC, factories) | Участник 1 |
| **2** | Модуль курсов (models, service, UI) | Участник 2 |
| **3** | Модуль заданий и оценок (Strategy pattern) | Участник 3 |
| **3** | Модуль расписания и посещаемости | Участник 4 |
| **4** | Модуль аналитики и экспорта (Strategy pattern) | Участник 5 |
| **5** | Интеграция модулей, тестирование, баг-фиксы | Все вместе |
| **6** | Полировка UI, документация, подготовка к защите | Все вместе |

---

## 📎 Полезные ссылки

- **Qt Documentation:** https://doc.qt.io/
- **Qt Signals & Slots:** https://doc.qt.io/qt-6/signalsandslots.html
- **QJsonDocument:** https://doc.qt.io/qt-6/qjsondocument.html
- **Design Patterns (Refactoring Guru, на русском):** https://refactoring.guru/ru/design-patterns
- **Singleton:** https://refactoring.guru/ru/design-patterns/singleton
- **Factory Method:** https://refactoring.guru/ru/design-patterns/factory-method
- **Strategy:** https://refactoring.guru/ru/design-patterns/strategy

---

## ⚡ Быстрая памятка для каждого участника

> **Прежде чем писать код, убедись, что ты:**
> 1. ✅ Прочитал весь README
> 2. ✅ Понял, какой модуль делаешь
> 3. ✅ Создал свою ветку (`feature/...`)
> 4. ✅ Посмотрел, от каких модулей зависишь
> 5. ✅ Договорился с теми участниками об интерфейсах (какие методы ты будешь вызывать)
> 6. ✅ Начал с `models/` → потом `services/` → потом `ui/`
> 7. ✅ Каждый класс наследуется от `SystemEntity`
> 8. ✅ Каждый класс реализует `toJson()` и `fromJson()`
> 9. ✅ Пишешь комментарии к коду
> 10. ✅ Коммитишь часто, с понятными сообщениями

---

*Сделано с ❤️ командой Study.Table();*
