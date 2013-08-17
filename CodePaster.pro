QT       += core gui xml gui-private
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CodePaster
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++0x

RESOURCES = images.qrc

SOURCES += src/main.cpp\
    src/searchwindow.cpp \
    src/searchbrowser.cpp \
    src/codepaster.cpp \
    src/codeeditorwindow.cpp \
    src/codeeditor.cpp \
    src/codebase.cpp \
    src/code.cpp \

HEADERS  += \
    src/searchwindow.h \
    src/searchbrowser.h \
    src/codepaster.h \
    src/codeeditorwindow.h \
    src/codeeditor.h \
    src/codebase.h \
    src/code.h \
win32
{
    RC_FILE += res.rc
    OTHER_FILES += res.rc
}

# Qxt
!macx:SOURCES += src/qxtglobalshortcut/qxtglobalshortcut.cpp
!macx:HEADERS += \
    src/qxtglobalshortcut/qxtglobalshortcut.h \
    src/qxtglobalshortcut/qxtglobal.h
win32:SOURCES += src/qxtglobalshortcut/qxtglobalshortcut_win.cpp
unix:!macx:SOURCES += src/qxtglobalshortcut/qxtglobalshortcut_x11.cpp
unix:!macx:LIBS += -lX11
