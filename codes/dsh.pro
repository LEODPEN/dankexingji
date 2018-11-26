#-------------------------------------------------
#
# Project created by QtCreator 2018-07-28T13:38:56
#
#-------------------------------------------------

QT       += core gui
QT       += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dsh
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        customerwindow.cpp \
    customer.cpp \
    user.cpp \
    boss.cpp \
    manager.cpp \
    executive.cpp \
    room.cpp \
    hotel.cpp \
    database.cpp \
    bosswindow.cpp \
    editroom.cpp \
    edithotel.cpp \
    addroom.cpp \
    addhotel.cpp \
    addaccount.cpp \
    hcomment.cpp \
    loginwindow.cpp \
    registerwindow.cpp \
    managerwindow.cpp \
    executivewindow.cpp

HEADERS += \
        customerwindow.h \
    customer.h \
    user.h \
    boss.h \
    manager.h \
    executive.h \
    room.h \
    hotel.h \
    database.h \
    registerwindow.h \
    bosswindow.h \
    editroom.h \
    edithotel.h \
    addroom.h \
    addhotel.h \
    addaccount.h \
    hcomment.h \
    enum.h \
    loginwindow.h \
    managerwindow.h \
    executivewindow.h

FORMS += \
    bosswindow.ui \
    edithotel.ui \
    addroom.ui \
    addhotel.ui \
    addaccount.ui \
    hcomment.ui \
    registerwindow.ui \
    loginwindow.ui \
    executivewindow.ui \
    editroom.ui \
    managerwindow.ui \
    customerwindow.ui

RESOURCES += \
    myimages.qrc
RC_ICONS = myico.ico
