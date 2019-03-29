#-------------------------------------------------
#
# Project created by QtCreator 2019-01-18T22:01:57
#
#-------------------------------------------------

QT       += core gui \
          multimedia


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mota_group
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

CONFIG += c++11

SOURCES += \
        main.cpp \
    Button.cpp \
    Msgboard.cpp \
    Map.cpp \
    Game.cpp \
    Hero.cpp \
    Monster.cpp \
    npc.cpp \
    Item.cpp \
    Unwalkable.cpp \
    battle.cpp \
    business.cpp \
    communication.cpp \
    subtitle.cpp \
    saveload.cpp \
    backpack.cpp \
    Mapfly.cpp \
    Choicerect.cpp

HEADERS += \
    Button.h \
    Button.h \
    Msgboard.h \
    Map.h \
    Game.h \
    Hero.h \
    Monster.h \
    npc.h \
    Item.h \
    Unwalkable.h \
    battle.h \
    business.h \
    communication.h \
    subtitle.h \
    saveload.h \
    backpack.h \
    Mapfly.h \
    Choicerect.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target



RESOURCES += \
    res.qrc
