QT       += core gui\
multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    shifter.cpp

HEADERS += \
    mainwindow.h\
    AudioFile.h \
    shifter.h


FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32: LIBS += -L$$PWD/Dependencies/fftw_dynamic/ -llibfftw3-3

INCLUDEPATH += $$PWD/Dependencies/fftw_dynamic
DEPENDPATH += $$PWD/Dependencies/fftw_dynamic
