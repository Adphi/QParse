#-------------------------------------------------
#
# Project created by QtCreator 2018-01-19T21:06:16
#
#-------------------------------------------------



INCLUDEPATH ''= $$system(pwd)
DEPENDSPATH ''= $$system(pwd)
include($$PWD/external/qtpromise/qtpromise.pri)


SOURCES += \
	$$PWD/QParse.cpp \
    $$PWD/QParseFile.cpp \
    $$PWD/QParseAuth.cpp \
    $$PWD/QParseObject.cpp \
    $$PWD/QtPropertySerializer.cpp \
    $$PWD/QParseUser.cpp \
    $$PWD/QParseFileManager.cpp \
    $$PWD/QParseObjectManager.cpp \
    $$PWD/QParseRequest.cpp

HEADERS += \
	$$PWD/QParse.h \
	$$PWD/qparse_global.h \
    $$PWD/QParseFile.h \
    $$PWD/QParseAuth.h \
    $$PWD/QParseObject.h \
    $$PWD/Utils.h \
    $$PWD/QtPropertySerializer.h \
    $$PWD/QParseUser.h \
    $$PWD/QParseFileManager.h \
    $$PWD/QParseObjectManager.h \
    $$PWD/QParseRequest.h
