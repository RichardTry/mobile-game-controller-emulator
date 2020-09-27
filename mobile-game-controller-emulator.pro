TEMPLATE = app

CONFIG += c++11

QT += widgets core gui network

SOURCES += \
    src/main.cpp

RESOURCES +=

INCLUDEPATH += include/

driver {
TARGET = driver-emulator
}

controller {
TARGET = controller-emulator
}

HEADERS += \
    include/controller/icontroller.h \
    include/emulator/icontrolleremulator.h \
    include/emulator/idriveremulator.h \
    include/input/icontinuousinput.h \
    include/input/idiscreteinput.h \
    include/transceiver/itransceiver.h
