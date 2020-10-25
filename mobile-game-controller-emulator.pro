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
    src/controller/icontroller.h \
    src/emulator/icontrolleremulator.h \
    src/emulator/idriveremulator.h \
    src/transceiver/abstracttransceiver.h

ANDROID_ABIS = armeabi-v7a
