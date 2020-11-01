#ifndef GAMEPADCONTROLLEREMULATOR_H
#define GAMEPADCONTROLLEREMULATOR_H

#include "emulator/icontrolleremulator.h"
#include <QObject>
#include <QWidget>

class GamepadControllerEmulator : public QObject, public IControllerEmulator {
    Q_OBJECT
public:
    GamepadControllerEmulator(QObject *parent = nullptr);
    ~GamepadControllerEmulator();

    void setTransceiver(AbstractTransceiver *transceiver) override;
    QWidget *widget() override;

private:
    AbstractTransceiver *m_transceiver;
    QWidget *m_widget;
};

#endif // GAMEPADCONTROLLEREMULATOR_H
