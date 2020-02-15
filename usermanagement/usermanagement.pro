#-------------------------------------------------
#
# Project created by QtCreator 2020-02-11T14:18:44
#
#-------------------------------------------------

QT       += core gui sql axcontainer widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = usermanagement
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainview.cpp \
    logindialog.cpp \
    userlogview.cpp \
    usermanagementview.cpp \
    adduserview.cpp \
    alteruserinfodialog.cpp \
    alteruserroledialog.cpp \
    rolepermissionsview.cpp \
    addroledialog.cpp \
    addpermissionsdialog.cpp \
    alterroleinfodialog.cpp \
    alterrolepmsdialog.cpp

HEADERS += \
        mainview.h \
    logindialog.h \
    userlogview.h \
    usermanagementview.h \
    adduserview.h \
    alteruserinfodialog.h \
    alteruserroledialog.h \
    rolepermissionsview.h \
    addroledialog.h \
    addpermissionsdialog.h \
    alterroleinfodialog.h \
    alterrolepmsdialog.h
