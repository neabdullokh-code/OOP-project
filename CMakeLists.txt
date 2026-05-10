cmake_minimum_required(VERSION 3.16)

project(StudyTable LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 QUIET COMPONENTS Widgets)
if(Qt6_FOUND)
    set(QT_LIB Qt6::Widgets)
else()
    find_package(Qt5 REQUIRED COMPONENTS Widgets)
    set(QT_LIB Qt5::Widgets)
endif()

set(PROJECT_SOURCES
    main.cpp

    core/authcontroller.cpp
    core/coursecontroller.cpp
    core/gradecontroller.cpp
    core/usercontroller.cpp

    core/databasemanager.cpp

    core/course.cpp
    core/enrollment.cpp
    core/grade.cpp
    core/user.cpp

    views/adminwindow.cpp
    views/loginwindow.cpp
    views/registrationwindow.cpp
    views/studentwindow.cpp
    views/teacherwindow.cpp

    views/adminwindow.ui
    views/loginwindow.ui
    views/registrationwindow.ui
    views/studentwindow.ui
    views/teacherwindow.ui
)

add_executable(StudyTable ${PROJECT_SOURCES})

target_include_directories(StudyTable PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/core
    ${CMAKE_CURRENT_SOURCE_DIR}/views
)

target_link_libraries(StudyTable PRIVATE ${QT_LIB})
