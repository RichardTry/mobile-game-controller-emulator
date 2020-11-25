#ifndef GAMEPADWIDGET_H
#define GAMEPADWIDGET_H

#include "controller/gamepad/gamepad.h"
#include "layout/gamepadsvglayout.h"
#include "widget/virtualdirectionalpad.h"
#include "widget/virtualanalogstick.h"
#include "widget/virtualgamepadbutton.h"
#include <QWidget>

class GamepadWidget : public QWidget {
    Q_OBJECT
public:
    explicit GamepadWidget(QWidget *parent = nullptr);

signals:
    void stickReleased(const Button& btn, const QPointF &point);
    void stickPressed(const Button& btn, const QPointF &point);
    void buttonReleased(const Button& btn);
    void buttonPressed(const Button& btn);

private:
    GamepadSvgLayout *m_svgLayout;
    VirtualDirectionalPad *m_dpad;
    VirtualAnalogStick *m_rightStick;
    VirtualAnalogStick *m_leftStick;
    // North, South, East, West in linux gamepad specs
    VirtualGamepadButton *m_a;
    VirtualGamepadButton *m_b;
    VirtualGamepadButton *m_x;
    VirtualGamepadButton *m_y;

    VirtualGamepadButton *m_start;
    VirtualGamepadButton *m_back;
};

#endif // GAMEPADWIDGET_H
