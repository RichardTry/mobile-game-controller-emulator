#ifndef GAMEPADCONTROLLEREMULATOR_H
#define GAMEPADCONTROLLEREMULATOR_H

#include "emulator/abstractcontrolleremulator.h"
#include "controller/gamepad/gamepad.h"
#include <QWidget>
#include <QSemaphore>

class GamepadControllerEmulator : public AbstractControllerEmulator {
    Q_OBJECT
public:
    GamepadControllerEmulator(QWidget *parent = nullptr);
    ~GamepadControllerEmulator();

    void setTransceiver(AbstractTransceiver *transceiver) override;

private:
    AbstractTransceiver *m_transceiver;
    Gamepad *m_gamepad;
    int m_payloadsBufferSize;
    QVector <QByteArray> m_payloads;
};

#endif // GAMEPADCONTROLLEREMULATOR_H
