TEMPLATE = app

CONFIG += c++11

QT += core gui widgets

DISTFILES +=

SOURCES += \
    src/main.cpp

RESOURCES += \
    resources.qrc

driver {
TARGET = controller-driver-emulator
}

controller {
TARGET = controller-emulator
}
