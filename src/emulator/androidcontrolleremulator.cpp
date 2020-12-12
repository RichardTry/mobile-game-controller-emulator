#include "androidcontrolleremulator.h"
#include <QEvent>
#include <QHBoxLayout>
#include <QAndroidJniObject>
#include <QtAndroid>
#include <QDebug>

AndroidControllerEmulator::AndroidControllerEmulator(AbstractTransceiver *transceiver, AbstractController *controller, QWidget *parent): AbstractControllerEmulator(transceiver, controller, parent), m_frameBufferSize(10) {
    m_frames.fill(QByteArray(), m_frameBufferSize);
    m_freeFrames.release(m_frameBufferSize);
    m_frameIndex = 0;

    this->setLayout(new QHBoxLayout);
    layout()->setContentsMargins(0, 0, 0, 0);
    layout()->addWidget(m_controller);

    connect(m_controller, &AbstractController::eventTriggered, this, &AndroidControllerEmulator::onEventTriggered);
    connect(m_controller, &AbstractController::stop, m_transceiver, &AbstractTransceiver::onStop);

    m_transmittionWorker = new TransmittionWorker(this);
    m_transmittionWorker->start();
}

AndroidControllerEmulator::~AndroidControllerEmulator() {
    m_transmittionWorker->stop();
    m_transmittionWorker->deleteLater();
}

void AndroidControllerEmulator::onEventTriggered(const QByteArray &data) {
    m_freeFrames.acquire();
    m_frameIndex = m_frameIndex % m_frameBufferSize;
    m_frames[m_frameIndex] = data;
    ++m_frameIndex;
    m_usedFrames.release();
}

AndroidControllerEmulator::TransmittionWorker::TransmittionWorker(AndroidControllerEmulator *emulator): m_emulator(emulator), m_stopped(false) {

}

void AndroidControllerEmulator::TransmittionWorker::run() {
    int index = 0;
    while(!m_stopped) {
        m_emulator->m_usedFrames.acquire();
        index %= m_emulator->m_frameBufferSize;
        QByteArray &payload = m_emulator->m_frames[index];
        ++index;
        m_emulator->m_transceiver->sendData(payload);
        m_emulator->m_freeFrames.release();
    }
}

void AndroidControllerEmulator::TransmittionWorker::stop() {
    m_stopped = true;
}

bool AndroidControllerEmulator::changeAndroidScreenOrientation(const Qt::ScreenOrientation &orientation) {
    QAndroidJniObject activity = QtAndroid::androidActivity();
    if ( activity.isValid() )
    {
        int code = 0;
        switch (orientation) {
        case Qt::LandscapeOrientation:
            code = 0;
            break;
        case Qt::PortraitOrientation:
            code = 1;
            break;
        case Qt::InvertedLandscapeOrientation:
            code = 0x8;
            break;
        case Qt::InvertedPortraitOrientation:
            code = 0x9;
            break;
        default:
            code = 0x4; // SCREEN_ORIENTATION_SENSOR
            break;
        }
        activity.callMethod<void>
                ("setRequestedOrientation" // method name
                 , "(I)V" // signature
                 , code);
        return true;
    }
    else
        return false;
}

void AndroidControllerEmulator::setVisible(bool visible) {
    if(visible)
        changeAndroidScreenOrientation(Qt::LandscapeOrientation);
    else
        changeAndroidScreenOrientation(Qt::PrimaryOrientation); // Defaults to sensor

    QWidget::setVisible(visible);
}
