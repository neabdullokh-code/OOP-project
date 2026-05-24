cmake_minimum_required(VERSION 3.16)

project(untitled VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
    main.cpp

    authcontroller.cpp
    authcontroller.h
    coursecontroller.cpp
    coursecontroller.h
    gradecontroller.cpp
    gradecontroller.h
    usercontroller.cpp
    usercontroller.h

    databasemanager.cpp
    databasemanager.h

    course.cpp
    course.h
    enrollment.cpp
    enrollment.h
    grade.cpp
    grade.h
    user.cpp
    user.h

    adminwindow.cpp
    adminwindow.h
    loginwindow.cpp
    loginwindow.h
    registrationwindow.cpp
    registrationwindow.h
    studentwindow.cpp
    studentwindow.h
    teacherwindow.cpp
    teacherwindow.h

    adminwindow.ui
    loginwindow.ui
    registrationwindow.ui
    studentwindow.ui
    teacherwindow.ui
)

add_executable(StudyTable ${PROJECT_SOURCES})

target_include_directories(StudyTable PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(StudyTable PRIVATE ${QT_LIB})
