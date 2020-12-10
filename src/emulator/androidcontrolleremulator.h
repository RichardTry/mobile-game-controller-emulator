#ifndef ANDROIDCONTROLLEREMULATOR_H
#define ANDROIDCONTROLLEREMULATOR_H

#include "emulator/abstractcontrolleremulator.h"
#include "controller/abstractcontroller.h"
#include "transceiver/abstracttransceiver.h"
#include <QWidget>
#include <QSemaphore>
#include <QThread>

class AndroidControllerEmulator : public AbstractControllerEmulator {
    Q_OBJECT

public:
    AndroidControllerEmulator(AbstractTransceiver *transceiver, AbstractController *controller, QWidget *parent = nullptr);
    ~AndroidControllerEmulator();

public slots:
    void onEventTriggered(const QByteArray &data) override;

private:
    class TransmittionWorker;
    TransmittionWorker *m_transmittionWorker;

    QAtomicInt m_frameIndex;
    int m_frameBufferSize;
    QVector <QByteArray> m_frames;
    QSemaphore m_freeFrames;
    QSemaphore m_usedFrames;
};

class AndroidControllerEmulator::TransmittionWorker: public QThread {
    Q_OBJECT
public:
    TransmittionWorker(AndroidControllerEmulator *emulator);
    void run() override;

public slots:
    void stop();

private:
    AndroidControllerEmulator *m_emulator;
    bool m_stopped;
};

#endif // ANDROIDCONTROLLEREMULATOR_H
