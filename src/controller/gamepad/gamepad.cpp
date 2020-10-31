#include "gamepad.h"
#include <QDataStream>

Gamepad::Gamepad() {

}

Gamepad::~Gamepad() {

}

QByteArray Gamepad::getData() const {
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);

    out << m_leftStick;
    out << m_rightStick;
    out << m_buttons;
    out << m_pressedEvents;
    out << m_releasedEvents;

    return data;
}

void Gamepad::setData(const QByteArray &data) {
    QByteArray dataCopy = data;
    QDataStream in(&dataCopy, QIODevice::ReadOnly);

    in >> m_leftStick;
    in >> m_rightStick;
    in >> m_buttons;
    in >> m_pressedEvents;
    in >> m_releasedEvents;

    m_xButton = X & m_buttons;
    m_yButton = Y & m_buttons;
    m_bButton = B & m_buttons;
    m_aButton = A & m_buttons;
    m_startButton = START & m_buttons;
    m_backButton = BACK & m_buttons;
    m_guideButton = GUIDE & m_buttons;
    m_leftTriggerButton = LEFTTRIGGER & m_buttons;
    m_rightTriggerButton = RIGHTTRIGGER & m_buttons;
    m_leftBumperButton = LEFTBUMPER & m_buttons;
    m_rightBumperButton = RIGHTBUMPER & m_buttons;
    m_upButton = UP & m_buttons;
    m_downButton = DOWN & m_buttons;
    m_leftButton = LEFT & m_buttons;
    m_rightButton = RIGHT & m_buttons;
}

QPointF Gamepad::getLeftStick() const
{
    return m_leftStick;
}

void Gamepad::setLeftStick(const QPointF &leftStick)
{
    m_leftStick = leftStick;
}

QPointF Gamepad::getRightStick() const
{
    return m_rightStick;
}

void Gamepad::setRightStick(const QPointF &rightStick)
{
    m_rightStick = rightStick;
}

bool Gamepad::getXButton() const
{
    return m_xButton;
}

void Gamepad::setXButton(bool xButton)
{
    m_xButton = xButton;
}

bool Gamepad::getYButton() const
{
    return m_yButton;
}

void Gamepad::setYButton(bool yButton)
{
    m_yButton = yButton;
}

bool Gamepad::getBButton() const
{
    return m_bButton;
}

void Gamepad::setBButton(bool bButton)
{
    m_bButton = bButton;
}

bool Gamepad::getAButton() const
{
    return m_aButton;
}

void Gamepad::setAButton(bool aButton)
{
    m_aButton = aButton;
}

bool Gamepad::getStartButton() const
{
    return m_startButton;
}

void Gamepad::setStartButton(bool startButton)
{
    m_startButton = startButton;
}

bool Gamepad::getBackButton() const
{
    return m_backButton;
}

void Gamepad::setBackButton(bool backButton)
{
    m_backButton = backButton;
}

bool Gamepad::getGuideButton() const
{
    return m_guideButton;
}

void Gamepad::setGuideButton(bool guideButton)
{
    m_guideButton = guideButton;
}

bool Gamepad::getLeftTriggerButton() const
{
    return m_leftTriggerButton;
}

void Gamepad::setLeftTriggerButton(bool leftTriggerButton)
{
    m_leftTriggerButton = leftTriggerButton;
}

bool Gamepad::getRightTriggerButton() const
{
    return m_rightTriggerButton;
}

void Gamepad::setRightTriggerButton(bool rightTriggerButton)
{
    m_rightTriggerButton = rightTriggerButton;
}

bool Gamepad::getLeftBumperButton() const
{
    return m_leftBumperButton;
}

void Gamepad::setLeftBumperButton(bool leftBumperButton)
{
    m_leftBumperButton = leftBumperButton;
}

bool Gamepad::getRightBumperButton() const
{
    return m_rightBumperButton;
}

void Gamepad::setRightBumperButton(bool rightBumperButton)
{
    m_rightBumperButton = rightBumperButton;
}

bool Gamepad::getUpButton() const
{
    return m_upButton;
}

void Gamepad::setUpButton(bool upButton)
{
    m_upButton = upButton;
}

bool Gamepad::getDownButton() const
{
    return m_downButton;
}

void Gamepad::setDownButton(bool downButton)
{
    m_downButton = downButton;
}

bool Gamepad::getLeftButton() const
{
    return m_leftButton;
}

void Gamepad::setLeftButton(bool leftButton)
{
    m_leftButton = leftButton;
}

bool Gamepad::getRightButton() const
{
    return m_rightButton;
}

void Gamepad::setRightButton(bool rightButton)
{
    m_rightButton = rightButton;
}
