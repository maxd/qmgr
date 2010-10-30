QT += core gui

TARGET = qmgr
TEMPLATE = app

!include(Resources/Resources.pri)
!include(FileList/FileList.pri)
!include(App/App.pri)

SOURCES += \
    main.cpp
