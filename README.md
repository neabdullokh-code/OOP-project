# StudyTable (OOP Project)

StudyTable is a Qt Widgets desktop application for simple course management with three user roles:
- **Admin**: manages courses and enrollments
- **Teacher**: views assigned courses and sets grades
- **Student**: views enrolled courses, grades, and average score

The app stores all data in local text files.

## Tech Stack

- C++
- Qt5/Qt6 Widgets
- CMake (minimum 3.16)

## Project Structure

- `main.cpp` – app entry point
- `filemanager.*` – data loading/saving and business logic
- `models.*` – domain models (User, Course, Enrollment, Grade)
- `*window.*` + `.ui` – role-based GUI windows
- `users.txt` – users data
- `courses.txt` – courses data
- `enrollments.txt` – enrollment data
- `grades.txt` – grades data

## Features

### Authentication
- Login with existing credentials
- Open registration window for new teacher/student accounts
- Built-in default admin creation on first run

### Admin
- View all users and courses
- Add new course (requires valid teacher ID)
- Enroll student to course (requires valid student ID and course ID)

### Teacher
- View own courses
- View students in those courses
- Set/update student grades (0–100)

### Student
- View enrolled courses
- View grades per course
- View average grade

## Build and Run

### Prerequisites

- CMake 3.16+
- C++17 compiler
- Qt development package (Qt5 or Qt6 with Widgets)

### Build

```bash
cd OOP-project
cmake -S . -B build
cmake --build build
```

### Run

After build, run the generated `StudyTable` executable from the build directory.

## Default Login

If `users.txt` is missing or empty, the app creates a default admin account:

- **Login:** `admin`
- **Password:** `admin123`

## Data File Format

All files use semicolon-separated fields (`;`), one record per line:

- `users.txt`: `id;login;password;fullName;role`
- `courses.txt`: `id;title;teacherId`
- `enrollments.txt`: `id;studentId;courseId`
- `grades.txt`: `id;enrollmentId;value`

## Notes

- Data is persisted immediately after successful operations.
- UI close button is disabled on role windows; use **Logout** to return to login.
- This is a local file-based educational project (no database, no network backend).
