#ifndef GAMEPADCONTROLLEREMULATOR_H
#define GAMEPADCONTROLLEREMULATOR_H

#include "emulator/abstractcontrolleremulator.h"
#include "controller/gamepad/gamepad.h"
#include "widget/gamepadwidget.h"
#include "transceiver/abstracttransceiver.h"
#include <QWidget>
#include <QSemaphore>
#include <QThread>

class GamepadControllerEmulator : public AbstractControllerEmulator {
    Q_OBJECT

public:
    GamepadControllerEmulator(AbstractTransceiver *transceiver, QWidget *parent = nullptr);
    ~GamepadControllerEmulator();

    void init() override;

private slots:
    void onStickMoved(const Button& btn, const QPointF &point);
    void onStickReleased(const Button& btn, const QPointF &point);
    void onStickPressed(const Button& btn, const QPointF &point);
    void onButtonReleased(const Button& btn);
    void onButtonPressed(const Button& btn);

private:
    class TransmittionWorker;
    TransmittionWorker *m_transmittionWorker;
    void writeFrame();
    Gamepad *m_gamepad;
    GamepadWidget *m_gamepadWidget;

    QAtomicInt m_frameIndex;
    int m_frameBufferSize;
    QVector <QByteArray> m_frames;
    QSemaphore m_freeFrames;
    QSemaphore m_usedFrames;
};

class GamepadControllerEmulator::TransmittionWorker: public QThread {
    Q_OBJECT
public:
    TransmittionWorker(GamepadControllerEmulator *emulator);
    void run() override;

public slots:
    void stop();

private:
    GamepadControllerEmulator *m_emulator;
    bool m_stopped;
};

#endif // GAMEPADCONTROLLEREMULATOR_H
