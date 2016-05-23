QT += core widgets

FORMS += \
    mainwindow.ui

HEADERS += \
    mainwindow.h \
    clock.h

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    clock.cpp

RESOURCES += \
    ../resources/resources.qrc

TARGET = "Fibonnac iClock"

QMAKE_INFO_PLIST = ../Info.plist

BUNDLE_DATA.files = ../resources/icon.png ../resources/green_tiles.png
QMAKE_BUNDLE_DATA += BUNDLE_DATA
