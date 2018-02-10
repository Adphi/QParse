#-------------------------------------------------
#
# Project created by QtCreator 2018-01-19T21:06:16
#
#-------------------------------------------------

QT       -= gui
QT	 += core network
TARGET = QParse
TEMPLATE = lib

DEFINES += QPARSE_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

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

unix {
    target.path = /usr/lib
    INSTALLS += target
}
