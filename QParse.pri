#-------------------------------------------------
#
# Project created by QtCreator 2018-01-19T21:06:16
#
#-------------------------------------------------



INCLUDEPATH ''= $$system(pwd)
DEPENDSPATH ''= $$system(pwd)
include($$PWD/external/qtpromise/qtpromise.pri)

INCLUDEPATH += $$PWD/QParseInstance \
	    $$PWD/QParseAuth \
	    $$PWD/QParseFile \
	    $$PWD/QParseObject \
	    $$PWD/QParseQuery \
	    $$PWD/QParseSerialize \
	    $$PWD/QParseUser

VPATH += $$PWD/QParseInstance \
	    $$PWD/QParseAuth \
	    $$PWD/QParseFile \
	    $$PWD/QParseObject \
	    $$PWD/QParseQuery \
	    $$PWD/QParseSerialize \
	    $$PWD/QParseUser

SOURCES += \
	QParse.cpp \
    QParseFile.cpp \
    QParseAuth.cpp \
    QParseUser.cpp \
    QParseFileManager.cpp \
    QParseObjectManager.cpp \
    QParseQuery.cpp \
    QParseObject.cpp \
    QtPropertySerializer.cpp \
    QParseJsonSerializer.cpp \

HEADERS += \
	QParse.h \
	qparse_global.h \
    QParseFile.h \
    QParseAuth.h \
    QParseUser.h \
    QParseFileManager.h \
    QParseObjectManager.h \
    QParseQuery.h \
    QParseObject.h \
    QtPropertySerializer.h \
    QParseJsonSerializer.h \
