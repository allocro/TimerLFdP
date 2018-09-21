QT += testlib
QT += gui
CONFIG += qt warn_on depend_includepath testcase
QT += widgets
TEMPLATE = app

SOURCES +=  tst_testcounter.cpp \
    counter.cpp

HEADERS += \
    counter.h
