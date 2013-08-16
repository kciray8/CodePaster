QT       += core gui xml
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CodePaster
TEMPLATE = app
QMAKE_CXXFLAGS += -std=gnu++11

RESOURCES = images.qrc

SOURCES += main.cpp\
     codebase.cpp \
    code.cpp \
    searchbrowser.cpp \
    searchwindow.cpp \
    codeeditorwindow.cpp \
    codeeditor.cpp \
    codepaster.cpp

HEADERS  += \
     codebase.h \
    code.h \
    searchbrowser.h \
    searchwindow.h \
    codeeditorwindow.h \
    codeeditor.h \
    codepaster.h

QXT     += core gui

win32{
    RC_FILE += res.rc
    OTHER_FILES += res.rc
}