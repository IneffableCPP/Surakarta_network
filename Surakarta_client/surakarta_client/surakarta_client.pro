QT       += core gui\
            network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    GameModel.cpp \
    main.cpp \
    main2.cpp \
    mainwindow.cpp \
    networkdata.cpp \
    networkserver.cpp \
    networksocket.cpp \
    piece.cpp \
    surakarta_agent_mine.cpp \
    surakarta_game.cpp \
    surakarta_reason.cpp \
    surakarta_rule_manager.cpp

HEADERS += \
    GameModel.h \
    mainwindow.h \
    networkdata.h \
    networkserver.h \
    networksocket.h \
    piece.h \
    surakarta_agent_base.h \
    surakarta_agent_mine.h \
    surakarta_board.h \
    surakarta_common.h \
    surakarta_game.h \
    surakarta_piece.h \
    surakarta_reason.h \
    surakarta_rule_manager.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
