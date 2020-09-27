TEMPLATE = app

CONFIG += c++11

QT += widgets core gui network

SOURCES += \
    src/main.cpp

RESOURCES +=

driver {
TARGET = driver-emulator
}

controller {
TARGET = controller-emulator
}
