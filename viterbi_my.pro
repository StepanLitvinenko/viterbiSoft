TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    viterbiSoft/viterbidecoder.cpp \
   # mycoder.cpp

HEADERS += \
    viterbiSoft/viterbidecoder.h \
   # mycoder.h
    filereader.h
