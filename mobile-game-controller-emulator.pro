TEMPLATE = app

CONFIG += c++11

QT += widgets core gui network xml svg

SOURCES += \
    src/controller/gamepad/gamepad.cpp \
    src/emulator/gamepad/gamepadcontrolleremulator.cpp \
    src/layout/gamepadsvglayout.cpp \
    src/main.cpp \
    src/transceiver/network/networktransceiver.cpp \
    src/widget/virtualanalogstick.cpp \
    src/widget/virtualdirectionalpad.cpp

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
    src/common/common.h \
    src/controller/gamepad/gamepad.h \
    src/controller/icontroller.h \
    src/emulator/abstractcontrolleremulator.h \
    src/emulator/gamepad/gamepadcontrolleremulator.h \
    src/emulator/idriveremulator.h \
    src/layout/gamepadsvglayout.h \
    src/transceiver/abstracttransceiver.h \
    src/transceiver/network/networktransceiver.h \
    src/widget/virtualanalogstick.h \
    src/widget/virtualdirectionalpad.h

ANDROID_ABIS = armeabi-v7a

FORMS += \
    ui/networktransceivermaster.ui \
    ui/networktransceiverslave.ui

DISTFILES += \
    android/AndroidManifest.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat \
    android/res/values/libs.xml \
    resources/controller-layout.svg

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
