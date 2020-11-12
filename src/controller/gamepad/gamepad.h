#ifndef GAMEPAD_H
#define GAMEPAD_H

#include "controller/icontroller.h"
#include "common/common.h"
#include <QPointF>
#include <QObject>

class Gamepad : public QObject, public IController {
    Q_OBJECT
public:
    Gamepad(QObject *parent = nullptr);
    ~Gamepad();

    QByteArray getData() override;
    void setData(const QByteArray &data) override;

signals:
    void buttonPressed(Button button);
    void buttonReleased(Button button);

public slots:
    void onButtonPressed(const Button &button);
    void onButtonReleased(const Button &button);

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
