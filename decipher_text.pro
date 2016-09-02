######################################################################
# Automatically generated by qmake (3.0) Mon Jul 25 19:13:41 2016
######################################################################

TEMPLATE = app
TARGET = decipher_text
INCLUDEPATH += inc

#DIRS
DESTDIR=bin
OBJECTS_DIR=obj

# Input
SOURCES += src/main.cxx

SOURCES += src/Control/ControlData.cxx
SOURCES += src/Control/Setting.cxx
SOURCES += src/Control/Language.cxx
SOURCES += src/Control/EventManager.cxx
SOURCES += src/Control/TesseractRecognize.cxx
SOURCES += src/Document/Page.cxx
SOURCES += src/Document/ProjectManager.cxx
SOURCES += src/Interface/MainWindow.cxx
SOURCES += src/Interface/Canvas.cxx
SOURCES += src/Interface/TextEditor.cxx
SOURCES += src/Interface/PageNav.cxx
SOURCES += src/Interface/SettingDialog.cxx
SOURCES += src/Interface/RecognizeProcess.cxx

#Link
LIBS += -llept
LIBS += -ltesseract

QT += widgets
QT += core

#CONFIG += c++11
CONFIG += console
