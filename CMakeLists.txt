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


    filemanager.cpp
    filemanager.h

    models.cpp
    models.h

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

target_link_libraries(StudyTable PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set(DATA_FILES
    users.txt
    courses.txt
    enrollments.txt
    grades.txt
)

foreach(DATA_FILE ${DATA_FILES})
    add_custom_command(TARGET StudyTable POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_SOURCE_DIR}/${DATA_FILE}
            $<TARGET_FILE_DIR:StudyTable>/${DATA_FILE}
    )
endforeach()
