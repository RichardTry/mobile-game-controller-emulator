#include "gamepad.h"
#include <QDataStream>
#include <QDebug>

Gamepad::Gamepad(QObject *parent ): QObject(parent), m_buttons(0), m_pressedEvents(0), m_releasedEvents(0), m_movedEvents(0) {

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
    out << m_movedEvents;

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
    in >> m_movedEvents;
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
}

void Gamepad::onStickMoved(const Button& button, const QPointF &point) {
    m_movedEvents |= button;
    if(button == Button::LEFTSTICK) {
        m_leftStick = point;
    } else if (button == Button::RIGHTSTICK) {
        m_rightStick = point;
    }
}

void Gamepad::onStickPressed(const Button& button, const QPointF &point) {
    m_buttons |= button;
    m_pressedEvents |= button;
    m_releasedEvents &= (~0) ^ button;
    if(button == Button::LEFTSTICK) {
        m_leftStick = point;
    } else if (button == Button::RIGHTSTICK) {
        m_rightStick = point;
    }
}

void Gamepad::onStickReleased(const Button& button, const QPointF &point) {
    m_buttons &= (~0) ^ button;
    m_releasedEvents |= button;
    m_pressedEvents &= (~0) ^ button;
    if(button == Button::LEFTSTICK) {
        m_leftStick = point;
    } else if (button == Button::RIGHTSTICK) {
        m_rightStick = point;
    }
}

void Gamepad::onButtonPressed(const Button &button) {
    m_buttons |= button;
    m_pressedEvents |= button;
    m_releasedEvents &= (~0) ^ button;
}

void Gamepad::onButtonReleased(const Button &button) {
    m_buttons &= (~0) ^ button;
    m_releasedEvents |= button;
    m_pressedEvents &= (~0) ^ button;
}

void Gamepad::clearEvents(const Button &button) {
    m_pressedEvents &= (~0) ^ button;
    m_releasedEvents &= (~0) ^ button;
    m_movedEvents &= (~0) ^ button;
}
