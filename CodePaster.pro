QT       += core gui xml
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CodePaster
TEMPLATE = app
QMAKE_CXXFLAGS += -std=gnu++11

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

win32{
    RC_FILE += res.rc
    OTHER_FILES += res.rc
}