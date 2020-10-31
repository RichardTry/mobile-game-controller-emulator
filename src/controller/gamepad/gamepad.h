#ifndef GAMEPAD_H
#define GAMEPAD_H

#include "controller/icontroller.h"
#include <QPointF>
#include <QtGlobal>

class Gamepad : public IController {
public:
    Gamepad();
    ~Gamepad();

    QByteArray getData() const override;
    void setData(const QByteArray &data) override;

    enum Button {
    // 4 Buttons on the right hands side
        X = 0,
        Y = 1,
        B = 2,
        A = 3,
    // Start, back and guide buttons in the middle
        START = 4,
        BACK = 5,
        GUIDE = 6,
    // 4 Buttons on the front facing side
        LEFTTRIGGER = 7,
        RIGHTTRIGGER = 8,
        LEFTBUMPER = 9,
        RIGHTBUMPER = 10,
    // D-Pad on the left hands side
        UP = 11,
        DOWN = 12,
        LEFT = 13,
        RIGHT = 14,
    };

    QPointF getLeftStick() const;
    void setLeftStick(const QPointF &leftStick);

    QPointF getRightStick() const;
    void setRightStick(const QPointF &rightStick);

    bool getXButton() const;
    void setXButton(bool xButton);

    bool getYButton() const;
    void setYButton(bool yButton);

    bool getBButton() const;
    void setBButton(bool bButton);

    bool getAButton() const;
    void setAButton(bool aButton);

    bool getStartButton() const;
    void setStartButton(bool startButton);

    bool getBackButton() const;
    void setBackButton(bool backButton);

    bool getGuideButton() const;
    void setGuideButton(bool guideButton);

    bool getLeftTriggerButton() const;
    void setLeftTriggerButton(bool leftTriggerButton);

    bool getRightTriggerButton() const;
    void setRightTriggerButton(bool rightTriggerButton);

    bool getLeftBumperButton() const;
    void setLeftBumperButton(bool leftBumperButton);

    bool getRightBumperButton() const;
    void setRightBumperButton(bool rightBumperButton);

    bool getUpButton() const;
    void setUpButton(bool upButton);

    bool getDownButton() const;
    void setDownButton(bool downButton);

    bool getLeftButton() const;
    void setLeftButton(bool leftButton);

    bool getRightButton() const;
    void setRightButton(bool rightButton);

protected:
    // Analog sticks
    QPointF m_leftStick;
    QPointF m_rightStick;
    // All button events and states are sent with these 3 variables
    quint32 m_buttons;
    quint32 m_pressedEvents;
    quint32 m_releasedEvents;

    bool m_xButton;
    bool m_yButton;
    bool m_bButton;
    bool m_aButton;
    bool m_startButton;
    bool m_backButton;
    bool m_guideButton;
    bool m_leftTriggerButton;
    bool m_rightTriggerButton;
    bool m_leftBumperButton;
    bool m_rightBumperButton;
    bool m_upButton;
    bool m_downButton;
    bool m_leftButton;
    bool m_rightButton;

};

#endif // GAMEPAD_H
