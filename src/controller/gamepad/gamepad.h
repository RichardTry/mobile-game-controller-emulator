#ifndef GAMEPAD_H
#define GAMEPAD_H

#include "controller/icontroller.h"
#include <QPointF>
#include <QObject>

class Gamepad : public IController, QObject {
    Q_OBJECT
public:
    Gamepad();
    ~Gamepad();

    QByteArray getData() override;
    void setData(const QByteArray &data) override;

    enum Button {
    // 4 Buttons on the right hands side
        X = 0,
        Y,
        B,
        A,
    // Start, back and guide buttons in the middle
        START,
        BACK,
        GUIDE,
    // 4 Buttons on the front facing side
        LEFTTRIGGER,
        RIGHTTRIGGER,
        LEFTBUMPER,
        RIGHTBUMPER,
    // D-Pad on the left hands side
        UP,
        DOWN,
        LEFT,
        RIGHT,
    };

signals:
    void buttonPressed(Button button);
    void buttonReleased(Button button);

public:
    bool getButton(Button button) const;
    void setButton(const Button &button, const bool &value);

    QPointF getLeftStick() const;
    void setLeftStick(const QPointF &leftStick);

    QPointF getRightStick() const;
    void setRightStick(const QPointF &rightStick);

private:
    // Data to send over transceiver
    QByteArray m_data;
    // Analog sticks
    QPointF m_leftStick;
    QPointF m_rightStick;
    // All button events and states are sent with these 3 variables
    quint32 m_buttons;
    quint32 m_pressedEvents;
    quint32 m_releasedEvents;
};

#endif // GAMEPAD_H
