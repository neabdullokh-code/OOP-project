QT       += core gui widgets

CONFIG   += c++17

TARGET = StudyTable
TEMPLATE = app

SOURCES += \
    main.cpp \
    models/user.cpp \
    models/course.cpp \
    models/grade.cpp \
    models/enrollment.cpp \
    database/databasemanager.cpp \
    controllers/authcontroller.cpp \
    controllers/usercontroller.cpp \
    controllers/coursecontroller.cpp \
    controllers/gradecontroller.cpp \
    views/loginwindow.cpp \
    views/adminpanel.cpp \
    views/teacherpanel.cpp \
    views/studentpanel.cpp

HEADERS += \
    models/user.h \
    models/course.h \
    models/grade.h \
    models/enrollment.h \
    database/databasemanager.h \
    controllers/authcontroller.h \
    controllers/usercontroller.h \
    controllers/coursecontroller.h \
    controllers/gradecontroller.h \
    views/loginwindow.h \
    views/adminpanel.h \
    views/teacherpanel.h \
    views/studentpanel.h

RESOURCES += \
    resources.qrc

# Default rules for deployment
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
