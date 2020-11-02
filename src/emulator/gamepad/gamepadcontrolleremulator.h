#ifndef GAMEPADCONTROLLEREMULATOR_H
#define GAMEPADCONTROLLEREMULATOR_H

#include "emulator/abstractcontrolleremulator.h"
#include "controller/gamepad/gamepad.h"
#include <QObject>
#include <QWidget>

class GamepadControllerEmulator : public AbstractControllerEmulator {
    Q_OBJECT
public:
    GamepadControllerEmulator(QWidget *parent = nullptr);
    ~GamepadControllerEmulator();

    void setTransceiver(AbstractTransceiver *transceiver) override;

private:
    AbstractTransceiver *m_transceiver;
    Gamepad *m_gamepad;
};

#endif // GAMEPADCONTROLLEREMULATOR_H
