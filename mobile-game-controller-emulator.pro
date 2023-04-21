TEMPLATE = app

CONFIG += c++11

QT += widgets core gui network svg

android {
QT += androidextras
}

SOURCES += \
    src/common/common.cpp \
    src/event/gamepadevent.cpp \
    src/layout/gamepadsvglayout.cpp \
    src/main.cpp \
    src/transceiver/networktransceiver.cpp \
    src/widget/networktransceiverwidget.cpp \
    src/widget/virtualanalogstick.cpp \
    src/widget/virtualdirectionalpad.cpp \
    src/widget/virtualgamepadbutton.cpp

RESOURCES += \
    resources/resources.qrc

INCLUDEPATH += src/

driver {
DEFINES += DRIVER
TARGET = driver-emulator

SOURCES += \
    src/driver/abstractdriver.cpp \
    src/driver/linuxgamepaddriver.cpp \
    src/emulator/genericdriveremulator.cpp

HEADERS += \
    src/driver/abstractdriver.h \
    src/driver/linuxgamepaddriver.h \
    src/emulator/abstractdriveremulator.h \
    src/emulator/genericdriveremulator.h \
}

controller {
DEFINES += CONTROLLER
TARGET = controller-emulator

SOURCES += \
    src/controller/gamepadcontroller.cpp \
    src/emulator/androidcontrolleremulator.cpp

HEADERS += \
    src/controller/abstractcontroller.h \
    src/controller/gamepadcontroller.h \
    src/emulator/abstractcontrolleremulator.h \
    src/emulator/androidcontrolleremulator.h \
}

HEADERS += \
    src/common/common.h \
    src/event/gamepadevent.h \
    src/layout/gamepadsvglayout.h \
    src/transceiver/abstracttransceiver.h \
    src/transceiver/networktransceiver.h \
    src/widget/networktransceiverwidget.h \
    src/widget/virtualanalogstick.h \
    src/widget/virtualdirectionalpad.h \
    src/widget/virtualgamepadbutton.h

ANDROID_ABIS = armeabi-v7a

FORMS += \
    ui/networktransceivermaster.ui \
    ui/networktransceiverslave.ui

android {
DISTFILES += \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat \
    android/res/values/libs.xml \
    android/AndroidManifest.xml

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
}

DISTFILES += \
    android/AndroidManifest.xml \
    android/build.gradle \
    android/gradle.properties \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat \
    android/res/values/libs.xml
