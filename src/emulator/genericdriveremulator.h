#ifndef GENERICDRIVEREMULATOR_H
#define GENERICDRIVEREMULATOR_H

#include "emulator/abstractdriveremulator.h"
#include <QThread>
#include <QSemaphore>

class GenericDriverEmulator : public AbstractDriverEmulator {
    Q_OBJECT
public:
    GenericDriverEmulator(AbstractDriver *driver, AbstractTransceiver *transceiver, QObject *parent = nullptr);
    ~GenericDriverEmulator();

public slots:
    void onError(QString error) override;
    void onDataArrived(QByteArray data) override;
    void onConnected() override;
    void onDisconnected(QString msg) override;
    void onQuit() override;

signals:
    void dataReadyForDriver(QByteArray data);

private:
    class TransmittionWorker;
    TransmittionWorker *m_transmittionWorker;

    QAtomicInt m_frameIndex;
    int m_frameBufferSize;
    QVector <QByteArray> m_frames;
    QSemaphore m_freeFrames;
    QSemaphore m_usedFrames;
};

class GenericDriverEmulator::TransmittionWorker: public QThread {
    Q_OBJECT
public:
    TransmittionWorker(GenericDriverEmulator *emulator);
    void run() override;

public slots:
    void stop();

private:
    GenericDriverEmulator *m_emulator;
    bool m_stopped;
};

#endif // GENERICDRIVEREMULATOR_H
