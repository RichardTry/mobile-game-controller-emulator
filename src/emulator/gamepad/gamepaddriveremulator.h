#ifndef GAMEPADDRIVEREMULATOR_H
#define GAMEPADDRIVEREMULATOR_H

#include "common/common.h"
#include "emulator/abstractdriveremulator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/input.h>
#include <linux/uinput.h>

class GamepadDriverEmulator : public AbstractDriverEmulator {
    Q_OBJECT
public:
    GamepadDriverEmulator(AbstractTransceiver *transceiver, QObject *parent = nullptr);
    ~GamepadDriverEmulator();

public slots:
    void onError(QString error) override;
    void onDataArrived(QByteArray data) override;
    void onConnected() override;
    void onDisconnected(QString msg) override;
    void onQuit() override;

    void onStickMoved(const Button& btn, const QPointF &point);
    void onStickReleased(const Button& btn, const QPointF &point);
    void onStickPressed(const Button& btn, const QPointF &point);
    void onButtonReleased(const Button &button);
    void onButtonPressed(const Button &button);

private:
    int init();
    struct input_event m_ev;
    struct uinput_user_dev m_uidev; //setting the default settings of Gamepad
    unsigned char m_toggle;
    int m_fd;
};

#endif // GAMEPADDRIVEREMULATOR_H
