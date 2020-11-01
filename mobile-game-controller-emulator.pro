TEMPLATE = app

CONFIG += c++11

QT += widgets core gui network svg

SOURCES += \
    src/controller/gamepad/gamepad.cpp \
    src/emulator/gamepad/gamepadcontrolleremulator.cpp \
    src/main.cpp \
    src/transceiver/network/networktransceiver.cpp \
    src/widget/virtualanalogstick.cpp

RESOURCES += \
    resources/resources.qrc

INCLUDEPATH += src/

driver {
DEFINES += DRIVER
TARGET = driver-emulator
}

controller {
DEFINES += CONTROLLER
TARGET = controller-emulator
}

HEADERS += \
    src/controller/gamepad/gamepad.h \
    src/controller/icontroller.h \
    src/emulator/gamepad/gamepadcontrolleremulator.h \
    src/emulator/icontrolleremulator.h \
    src/emulator/idriveremulator.h \
    src/transceiver/abstracttransceiver.h \
    src/transceiver/network/networktransceiver.h \
    src/widget/virtualanalogstick.h

ANDROID_ABIS = armeabi-v7a

FORMS += \
    ui/networktransceivermaster.ui \
    ui/networktransceiverslave.ui
