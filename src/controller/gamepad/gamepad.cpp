#include "gamepad.h"
#include <QDataStream>
#include <QDebug>

Gamepad::Gamepad(QObject *parent ): QObject(parent), m_buttons(0), m_pressedEvents(0), m_releasedEvents(0) {

}

Gamepad::~Gamepad() {

}

QByteArray Gamepad::getData() {
    m_data.clear();
    QDataStream out(&m_data, QIODevice::WriteOnly);

    out << m_leftStick;
    out << m_rightStick;
    out << m_buttons;
    out << m_pressedEvents;
    out << m_releasedEvents;

    return m_data;
}

void Gamepad::setData(const QByteArray &data) {
    m_data = data;
    QDataStream in(&m_data, QIODevice::ReadOnly);

    in >> m_leftStick;
    in >> m_rightStick;
    in >> m_buttons;
    in >> m_pressedEvents;
    in >> m_releasedEvents;
}

QPointF Gamepad::getLeftStick() const {
    return m_leftStick;
}

void Gamepad::setLeftStick(const QPointF &leftStick) {
    m_leftStick = leftStick;
}

QPointF Gamepad::getRightStick() const {
    return m_rightStick;
}

void Gamepad::setRightStick(const QPointF &rightStick){
    m_rightStick = rightStick;
}

bool Gamepad::getButton(Button button) const {
    return m_buttons & button;
}

void Gamepad::setButton(const Button &button, const bool &value) {
    if(value) {
        m_buttons |= button;
    } else {
        m_buttons &= (~0) ^ button;
    }
    qDebug() << QString::number(m_buttons, 2);
}
