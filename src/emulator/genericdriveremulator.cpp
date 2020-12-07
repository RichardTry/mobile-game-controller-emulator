#include "genericdriveremulator.h"
#include "transceiver/abstracttransceiver.h"
#include "driver/abstractdriver.h"

GenericDriverEmulator::GenericDriverEmulator(AbstractDriver *driver, AbstractTransceiver *transceiver, QObject *parent):
    AbstractDriverEmulator(driver, transceiver, parent),
    m_frameBufferSize(10)
{
    m_frames.fill(QByteArray(), m_frameBufferSize);
    m_freeFrames.release(m_frameBufferSize);
    m_frameIndex = 0;

    m_transmittionWorker = new TransmittionWorker(this);
    m_transmittionWorker->start();

    connect(transceiver, &AbstractTransceiver::dataArrived, this, &GenericDriverEmulator::onDataArrived);
}

GenericDriverEmulator::~GenericDriverEmulator() {
    m_transmittionWorker->stop();
    m_transmittionWorker->deleteLater();
}

void GenericDriverEmulator::onError(QString error) {

}

void GenericDriverEmulator::onDataArrived(QByteArray data) {
    m_freeFrames.acquire();
    m_frameIndex = m_frameIndex % m_frameBufferSize;
    m_frames[m_frameIndex] = data;
    ++m_frameIndex;
    m_usedFrames.release();
}

void GenericDriverEmulator::onConnected() {

}

void GenericDriverEmulator::onDisconnected(QString msg) {

}

void GenericDriverEmulator::onQuit() {

}

GenericDriverEmulator::TransmittionWorker::TransmittionWorker(GenericDriverEmulator *emulator): m_emulator(emulator), m_stopped(false) {

}

void GenericDriverEmulator::TransmittionWorker::run() {
    int index = 0;
    while(!m_stopped) {
        m_emulator->m_usedFrames.acquire();
        index %= m_emulator->m_frameBufferSize;
        QByteArray &payload = m_emulator->m_frames[index];
        ++index;
        m_emulator->m_driver->onDataArrived(payload);
        m_emulator->m_freeFrames.release();
    }
}

void GenericDriverEmulator::TransmittionWorker::stop() {
    m_stopped = true;
}
