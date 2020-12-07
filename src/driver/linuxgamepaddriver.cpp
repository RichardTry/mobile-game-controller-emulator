#include "linuxgamepaddriver.h"
#include "controller/gamepadcontroller.h"
#include <QDebug>

LinuxGamepadDriver::LinuxGamepadDriver(QObject *parent): AbstractDriver(parent) {
}

void LinuxGamepadDriver::onDataArrived(const QByteArray &data) {
    GamepadController::GamepadEvent event(data);

    const QString btnLabel = labelForButton(event.m_button);
    switch (event.m_type) {
    case GamepadController::GamepadEvent::ButtonPressEvent: {
        qDebug() << QString("Button pressed:").leftJustified(50) << btnLabel.rightJustified(10, ' ');
    }
    case GamepadController::GamepadEvent::ButtonReleaseEvent: {
        qDebug() << QString("Button released:").leftJustified(50) << btnLabel.rightJustified(10, ' ');
    }
    case GamepadController::GamepadEvent::StickMoveEvent: {
        qDebug() << QString(btnLabel + " Moved:").leftJustified(50)
                 << QString::number(event.m_value.x()).rightJustified(10)
                 << " "
                 << QString::number(event.m_value.y()).rightJustified(10);
    }
    case GamepadController::GamepadEvent::StickPressEvent: {
        qDebug() << QString(btnLabel + " Pressed:").leftJustified(50)
                 << QString::number(event.m_value.x()).rightJustified(10)
                 << " "
                 << QString::number(event.m_value.y()).rightJustified(10);
    }
    case GamepadController::GamepadEvent::StickReleaseEvent: {
        qDebug() << QString(btnLabel + " Released:").leftJustified(50)
                 << QString::number(event.m_value.x()).rightJustified(10)
                 << " "
                 << QString::number(event.m_value.y()).rightJustified(10);
    }

    }
}
