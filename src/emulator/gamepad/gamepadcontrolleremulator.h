#ifndef GAMEPADCONTROLLEREMULATOR_H
#define GAMEPADCONTROLLEREMULATOR_H

#include "emulator/abstractcontrolleremulator.h"
#include "controller/gamepad/gamepad.h"
#include "layout/gamepadsvglayout.h"
#include "widget/virtualdirectionalpad.h"
#include "widget/virtualanalogstick.h"
#include "widget/virtualgamepadbutton.h"
#include <QWidget>

class GamepadControllerEmulator : public AbstractControllerEmulator {
    Q_OBJECT
public:
    GamepadControllerEmulator(QWidget *parent = nullptr);
    ~GamepadControllerEmulator();

    void setTransceiver(AbstractTransceiver *transceiver) override;

protected:
    bool event(QEvent *event) override;

private:
    AbstractTransceiver *m_transceiver;
    Gamepad *m_gamepad;
    GamepadSvgLayout *m_svgLayout;
    VirtualDirectionalPad *m_dpad;
    VirtualAnalogStick *m_rightStick;
    VirtualAnalogStick *m_leftStick;

    VirtualGamepadButton *m_a;
    VirtualGamepadButton *m_b;
    VirtualGamepadButton *m_x;
    VirtualGamepadButton *m_y;

    VirtualGamepadButton *m_start;
    VirtualGamepadButton *m_back;
};

#endif // GAMEPADCONTROLLEREMULATOR_H
