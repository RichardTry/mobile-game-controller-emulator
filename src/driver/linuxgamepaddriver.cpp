#include "linuxgamepaddriver.h"
#include "controller/gamepadcontroller.h"
#include <QDebug>

LinuxGamepadDriver::LinuxGamepadDriver(QObject *parent): AbstractDriver(parent) {
}

void LinuxGamepadDriver::onDataArrived(const QByteArray &data) {
    GamepadController::GamepadEvent event(data);

    const int infoTextWidth = 20;
    const int numberWidth = 15;
    const QString btnLabel = labelForButton(event.m_button);
    switch (event.m_type) {
    case GamepadController::GamepadEvent::ButtonPressEvent: {
        qDebug() << QString("Button pressed:").leftJustified(infoTextWidth) << btnLabel.rightJustified(numberWidth, ' ');
        break;
    }
    case GamepadController::GamepadEvent::ButtonReleaseEvent: {
        qDebug() << QString("Button released:").leftJustified(infoTextWidth) << btnLabel.rightJustified(numberWidth, ' ');
        break;
    }
    case GamepadController::GamepadEvent::StickMoveEvent: {
        qDebug() << QString(btnLabel + " Moved:").leftJustified(infoTextWidth)
                 << QString::number(event.m_value.x()).rightJustified(numberWidth)
                 << " "
                 << QString::number(event.m_value.y()).rightJustified(numberWidth);
        break;
    }
    case GamepadController::GamepadEvent::StickPressEvent: {
        qDebug() << QString(btnLabel + " Pressed:").leftJustified(infoTextWidth)
                 << QString::number(event.m_value.x()).rightJustified(numberWidth)
                 << " "
                 << QString::number(event.m_value.y()).rightJustified(numberWidth);
        break;
    }
    case GamepadController::GamepadEvent::StickReleaseEvent: {
        qDebug() << QString(btnLabel + " Released:").leftJustified(infoTextWidth)
                 << QString::number(event.m_value.x()).rightJustified(numberWidth)
                 << " "
                 << QString::number(event.m_value.y()).rightJustified(numberWidth);
        break;
    }

    }
}
