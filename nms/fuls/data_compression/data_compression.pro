TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        compDriver.cpp \
        fgk.cpp \
        fileOps.cpp \
        huffstat.cpp \
        lz77.cpp \
        lz78.cpp \
        main.cpp \
        rle.cpp \
        sf.cpp \
        vit.cpp

HEADERS += \
    compDriver.h \
    fgk.h \
    fileOps.h \
    huffstat.h \
    lz77.h \
    lz78.h \
    rle.h \
    sf.h \
    vit.h
