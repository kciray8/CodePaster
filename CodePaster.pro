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
    contrib/utils/usettings.cpp \
    contrib/utils/ukeysequence.cpp \
    contrib/utils/uglobalhotkeys.cpp \
    contrib/utils/ufullscreenwrapper.cpp \
    contrib/utils/uexception.cpp \
    contrib/utils/ucolonsep.cpp \
    contrib/utils/ucast.cpp

HEADERS  += \
    src/searchwindow.h \
    src/searchbrowser.h \
    src/codepaster.h \
    src/codeeditorwindow.h \
    src/codeeditor.h \
    src/codebase.h \
    src/code.h \
    contrib/utils/usettings.h \
    contrib/utils/ukeysequence.h \
    contrib/utils/uglobalhotkeys.h \
    contrib/utils/ufullscreenwrapper.h \
    contrib/utils/uexception.h \
    contrib/utils/udebug.h \
    contrib/utils/ucolonsep.h \
    contrib/utils/ucast.h \
    contrib/utils/hotkeymap.h

win32{
    RC_FILE += res.rc
    OTHER_FILES += res.rc
}